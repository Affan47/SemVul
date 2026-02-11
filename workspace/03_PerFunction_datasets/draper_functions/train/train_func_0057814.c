i40e_fdir_filter_exit(struct i40e_pf *pf)
{
	struct i40e_fdir_filter *filter;
	struct hlist_node *node2;

	hlist_for_each_entry_safe(filter, node2,
				  &pf->fdir_filter_list, fdir_node) {
		hlist_del(&filter->fdir_node);
		kfree(filter);
	}
	pf->fdir_pf_active_filters = 0;
}
