brcmf_commonring_get_read_ptr(struct brcmf_commonring *commonring,
				    u16 *n_items)
{
	if (commonring->cr_update_wptr)
		commonring->cr_update_wptr(commonring->cr_ctx);

	*n_items = (commonring->w_ptr >= commonring->r_ptr) ?
				(commonring->w_ptr - commonring->r_ptr) :
				(commonring->depth - commonring->r_ptr);

	if (*n_items == 0)
		return NULL;

	return commonring->buf_addr +
	       (commonring->r_ptr * commonring->item_len);
}
