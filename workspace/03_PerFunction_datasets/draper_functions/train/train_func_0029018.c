cifs_user_writev(struct kiocb *iocb, struct iov_iter *from)
{
	struct file *file = iocb->ki_filp;
	ssize_t total_written = 0;
	struct cifsFileInfo *open_file;
	struct cifs_tcon *tcon;
	struct cifs_sb_info *cifs_sb;
	struct cifs_writedata *wdata, *tmp;
	struct list_head wdata_list;
	struct iov_iter saved_from;
	int rc;


	rc = generic_write_checks(iocb, from);
	if (rc <= 0)
		return rc;

	INIT_LIST_HEAD(&wdata_list);
	cifs_sb = CIFS_FILE_SB(file);
	open_file = file->private_data;
	tcon = tlink_tcon(open_file->tlink);

	if (!tcon->ses->server->ops->async_writev)
		return -ENOSYS;

	memcpy(&saved_from, from, sizeof(struct iov_iter));

	rc = cifs_write_from_iter(iocb->ki_pos, iov_iter_count(from), from,
				  open_file, cifs_sb, &wdata_list);


	if (!list_empty(&wdata_list))
		rc = 0;


restart_loop:
	list_for_each_entry_safe(wdata, tmp, &wdata_list, list) {
		if (!rc) {

			rc = wait_for_completion_killable(&wdata->done);
			if (rc)
				rc = -EINTR;
			else if (wdata->result)
				rc = wdata->result;
			else
				total_written += wdata->bytes;


			if (rc == -EAGAIN) {
				struct list_head tmp_list;
				struct iov_iter tmp_from;

				INIT_LIST_HEAD(&tmp_list);
				list_del_init(&wdata->list);

				memcpy(&tmp_from, &saved_from,
				       sizeof(struct iov_iter));
				iov_iter_advance(&tmp_from,
						 wdata->offset - iocb->ki_pos);

				rc = cifs_write_from_iter(wdata->offset,
						wdata->bytes, &tmp_from,
						open_file, cifs_sb, &tmp_list);

				list_splice(&tmp_list, &wdata_list);

				kref_put(&wdata->refcount,
					 cifs_uncached_writedata_release);
				goto restart_loop;
			}
		}
		list_del_init(&wdata->list);
		kref_put(&wdata->refcount, cifs_uncached_writedata_release);
	}

	if (unlikely(!total_written))
		return rc;

	iocb->ki_pos += total_written;
	set_bit(CIFS_INO_INVALID_MAPPING, &CIFS_I(file_inode(file))->flags);
	cifs_stats_bytes_written(tcon, total_written);
	return total_written;
}
