row_purge_reposition_pcur(

	ulint		mode,
	purge_node_t*	node,
	mtr_t*		mtr)
{
	ibool	found;

	if (node->found_clust) {
		found = btr_pcur_restore_position(mode, &(node->pcur), mtr);

		return(found);
	}

	found = row_search_on_row_ref(&(node->pcur), mode, node->table,
				      node->ref, mtr);
	node->found_clust = found;

	if (found) {
		btr_pcur_store_position(&(node->pcur), mtr);
	}

	return(found);
}
