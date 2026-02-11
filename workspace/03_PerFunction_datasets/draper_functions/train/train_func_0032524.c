ndmp_sxa_fh_add_file (struct ndm_session *sess,
  struct ndmp_xa_buf *xa, struct ndmconn *ref_conn)
{
	struct ndm_control_agent *ca = &sess->control_acb;
	struct ndmlog *		ixlog = &ca->job.index_log;
	int			tagc = ref_conn->chan.name[1];
	unsigned int		i;
	ndmp9_file *		file;

	xa->reply.flags |= NDMNMB_FLAG_NO_SEND;

	NDMS_WITH_NO_REPLY(ndmp9_fh_add_file)
		for (i = 0; i < request->files.files_len; i++) {
			file = &request->files.files_val[i];

			ndmfhdb_add_file (ixlog, tagc,
				file->unix_path, &file->fstat);
		}
	NDMS_ENDWITH

	return 0;
}
