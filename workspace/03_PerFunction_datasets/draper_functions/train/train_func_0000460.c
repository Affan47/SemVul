compare_arrays(Module_table *mpt, SemBranch *lBranch, SemBranch *rBranch)
{
    int l_array, r_array, i;
    Array_table *l_arrays, *r_arrays, *l_arrays_head, *r_arrays_head;
    char *checked;
    l_arrays_head = construct_arraylist_from_semtree(lBranch);
    if(l_arrays_head != NULL && l_arrays_head->entry == -1){
        free_array_table(l_arrays_head);
        return FALSE;
    }
    l_array = count_arraylist(l_arrays_head);

    r_arrays_head = construct_arraylist_from_semtree(rBranch);
    if(r_arrays_head != NULL && r_arrays_head->entry == -1){
        free_array_table(l_arrays_head);
        free_array_table(r_arrays_head);
        return FALSE;
    }
    r_array = count_arraylist(r_arrays_head);
    checked = calloc(r_array, sizeof(char*));
    for(l_arrays = l_arrays_head, r_arrays = r_arrays_head;
	l_arrays != NULL;
	l_arrays = l_arrays->next){
	Array_table *tr_arrays = NULL;
	for(tr_arrays = r_arrays, i = 0;
	    tr_arrays != NULL;
	    tr_arrays = tr_arrays->next, i++){
	    if(checked[i]) continue;
            if(tr_arrays->entry == l_arrays->entry) {
                if(!compare_subtree(mpt,
				    get_array_subscript_from_branch(lBranch, tr_arrays->entry),
				    get_array_subscript_from_branch(rBranch, tr_arrays->entry))){
		    free_array_table(l_arrays_head);
		    free_array_table(r_arrays_head);
		    free(checked);
		    return FALSE;
		}else{
		    checked[i] = 1;
		    l_array--;
		    r_array--;
		    break;
		}
            }
	}
    }
    free_array_table(l_arrays_head);
    free_array_table(r_arrays_head);
    free(checked);
    if(l_array == 0 && r_array == 0) {
	return TRUE;
    }

    return FALSE;
}
