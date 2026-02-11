get_tlg_array_size_by_du_table(Block *block_head,
			       int Tlg_no)
{

    Block *bpt;
    Array_def_use_table *tlg_du_array = NULL;

    for (bpt = block_head; bpt != NULL; bpt = bpt->next) {
	if (bpt->tlg_tag == Tlg_no) {
	    union_array_def_use_table(&tlg_du_array, bpt->MayMod);
	    union_array_def_use_table(&tlg_du_array, bpt->MayUse);
	}
    }
    return get_array_du_estimated_size(tlg_du_array, block_head);
}
