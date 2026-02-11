set_galms_target_mpt_body(Array_table *array_head, Module_table *mpt, int *array_size,
			  Galms *galms, IntSet local_array, int *count,
			  real **target_gain)
{
    Array_table *atbl = NULL;
    for (atbl = array_head; atbl != NULL; atbl = atbl->next) {
        int entry = atbl->entry;
	int size;
        if (in_IntSet(local_array, entry)) {
            size = array_size[entry];
            galms[*count].gain = target_gain[mpt->entry][entry] / size;
            galms[*count].tbl.a = atbl;
            galms[*count].module = mpt;
	    galms[*count].local_array = local_array;
            galms[*count].size = size;
            (*count) = (*count) + 1;
        }
    }

}
