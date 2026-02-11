xfs_cil_prepare_item(
	struct xlog		*log,
	struct xfs_log_vec	*lv,
	struct xfs_log_vec	*old_lv,
	int			*diff_len,
	int			*diff_iovecs)
{

	if (lv->lv_buf_len != XFS_LOG_VEC_ORDERED) {
		*diff_len += lv->lv_bytes;
		*diff_iovecs += lv->lv_niovecs;
	}


	if (!old_lv)
		lv->lv_item->li_ops->iop_pin(lv->lv_item);
	else if (old_lv != lv) {
		ASSERT(lv->lv_buf_len != XFS_LOG_VEC_ORDERED);

		*diff_len -= old_lv->lv_bytes;
		*diff_iovecs -= old_lv->lv_niovecs;
		kmem_free(old_lv);
	}


	lv->lv_item->li_lv = lv;


	if (!lv->lv_item->li_seq)
		lv->lv_item->li_seq = log->l_cilp->xc_ctx->sequence;
}
