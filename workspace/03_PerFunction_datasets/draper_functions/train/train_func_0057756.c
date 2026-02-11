innobase_index_lookup(

	INNOBASE_SHARE*	share,

	uint		keynr)

{
	if (!share->idx_trans_tbl.index_mapping
	    || keynr >= share->idx_trans_tbl.index_count) {
		return(NULL);
	}

	return(share->idx_trans_tbl.index_mapping[keynr]);
}
