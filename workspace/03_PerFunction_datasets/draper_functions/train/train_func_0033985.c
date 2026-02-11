send_write(struct send_ctx *sctx, u64 offset, u32 len)
{
	int ret = 0;
	struct fs_path *p;
	ssize_t num_read = 0;

	p = fs_path_alloc();
	if (!p)
		return -ENOMEM;

verbose_printk("btrfs: send_write offset=%llu, len=%d\n", offset, len);

	num_read = fill_read_buf(sctx, offset, len);
	if (num_read <= 0) {
		if (num_read < 0)
			ret = num_read;
		goto out;
	}

	ret = begin_cmd(sctx, BTRFS_SEND_C_WRITE);
	if (ret < 0)
		goto out;

	ret = get_cur_path(sctx, sctx->cur_ino, sctx->cur_inode_gen, p);
	if (ret < 0)
		goto out;

	TLV_PUT_PATH(sctx, BTRFS_SEND_A_PATH, p);
	TLV_PUT_U64(sctx, BTRFS_SEND_A_FILE_OFFSET, offset);
	TLV_PUT(sctx, BTRFS_SEND_A_DATA, sctx->read_buf, num_read);

	ret = send_cmd(sctx);

tlv_put_failure:
out:
	fs_path_free(p);
	if (ret < 0)
		return ret;
	return num_read;
}
