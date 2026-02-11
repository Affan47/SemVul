row_purge_poss_sec(

	purge_node_t*	node,
	dict_index_t*	index,
	const dtuple_t*	entry)
{
	ibool	can_delete;
	mtr_t	mtr;

	ut_ad(!dict_index_is_clust(index));
	mtr_start(&mtr);

	can_delete = !row_purge_reposition_pcur(BTR_SEARCH_LEAF, node, &mtr)
		|| !row_vers_old_has_index_entry(TRUE,
						 btr_pcur_get_rec(&node->pcur),
						 &mtr, index, entry);

	btr_pcur_commit_specify_mtr(&node->pcur, &mtr);

	return(can_delete);
}
