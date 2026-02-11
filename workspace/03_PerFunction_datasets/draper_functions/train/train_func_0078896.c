__frontswap_invalidate_page(unsigned type, pgoff_t offset)
{
	struct swap_info_struct *sis = swap_info[type];
	struct frontswap_ops *ops;

	if (!frontswap_ops)
		return;

	BUG_ON(sis == NULL);
	if (!__frontswap_test(sis, offset))
		return;

	for_each_frontswap_ops(ops)
		ops->invalidate_page(type, offset);
	__frontswap_clear(sis, offset);
	inc_frontswap_invalidates();
}
