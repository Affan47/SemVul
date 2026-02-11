xlog_write_calc_vec_length(
	struct xlog_ticket	*ticket,
	struct xfs_log_vec	*log_vector)
{
	struct xfs_log_vec	*lv;
	int			headers = 0;
	int			len = 0;
	int			i;


	if (ticket->t_flags & XLOG_TIC_INITED)
		headers++;

	for (lv = log_vector; lv; lv = lv->lv_next) {

		if (lv->lv_buf_len == XFS_LOG_VEC_ORDERED)
			continue;

		headers += lv->lv_niovecs;

		for (i = 0; i < lv->lv_niovecs; i++) {
			struct xfs_log_iovec	*vecp = &lv->lv_iovecp[i];

			len += vecp->i_len;
			xlog_tic_add_region(ticket, vecp->i_len, vecp->i_type);
		}
	}

	ticket->t_res_num_ophdrs += headers;
	len += headers * sizeof(struct xlog_op_header);

	return len;
}
