receive_rcom_names(struct dlm_ls *ls, struct dlm_rcom *rc_in)
{
	struct dlm_rcom *rc;
	struct dlm_mhandle *mh;
	int error, inlen, outlen, nodeid;

	nodeid = rc_in->rc_header.h_nodeid;
	inlen = rc_in->rc_header.h_length - sizeof(struct dlm_rcom);
	outlen = dlm_config.ci_buffer_size - sizeof(struct dlm_rcom);

	error = create_rcom(ls, nodeid, DLM_RCOM_NAMES_REPLY, outlen, &rc, &mh);
	if (error)
		return;
	rc->rc_id = rc_in->rc_id;
	rc->rc_seq_reply = rc_in->rc_seq;

	dlm_copy_master_names(ls, rc_in->rc_buf, inlen, rc->rc_buf, outlen,
			      nodeid);
	send_rcom(ls, mh, rc);
}
