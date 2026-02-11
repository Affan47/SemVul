hb_itor_set_data(hb_itor *itor, void *dat, int del)
{
	ASSERT(itor != NULL);

	if (itor->node == NULL)
		return -1;

	if (del && itor->tree->dat_del)
		itor->tree->dat_del(itor->node->dat);
	itor->node->dat = dat;
	return 0;
}
