xlog_recover_add_to_cont_trans(
	struct xlog		*log,
	struct xlog_recover	*trans,
	char			*dp,
	int			len)
{
	xlog_recover_item_t	*item;
	char			*ptr, *old_ptr;
	int			old_len;


	if (list_empty(&trans->r_itemq)) {
		ASSERT(len <= sizeof(struct xfs_trans_header));
		if (len > sizeof(struct xfs_trans_header)) {
			xfs_warn(log->l_mp, "%s: bad header length", __func__);
			return -EIO;
		}

		xlog_recover_add_item(&trans->r_itemq);
		ptr = (char *)&trans->r_theader +
				sizeof(struct xfs_trans_header) - len;
		memcpy(ptr, dp, len);
		return 0;
	}


	item = list_entry(trans->r_itemq.prev, xlog_recover_item_t, ri_list);

	old_ptr = item->ri_buf[item->ri_cnt-1].i_addr;
	old_len = item->ri_buf[item->ri_cnt-1].i_len;

	ptr = kmem_realloc(old_ptr, len+old_len, old_len, KM_SLEEP);
	memcpy(&ptr[old_len], dp, len);
	item->ri_buf[item->ri_cnt-1].i_len += len;
	item->ri_buf[item->ri_cnt-1].i_addr = ptr;
	trace_xfs_log_recover_item_add_cont(log, trans, item, 0);
	return 0;
}
