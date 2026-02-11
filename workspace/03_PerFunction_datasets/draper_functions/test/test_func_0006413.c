add_aster_array_du_in_sb( Block *loop, Block *sb )
{
    Depend_array *dep_arr, *apt;
    IntSet du_arr_bv;
    IntSet def_arr_bv = loop->def_var_list->array_bv;
    IntSet use_arr_bv = loop->use_var_list->array_bv;
    int i, max;
    Statement *call_stm = get_call_stm_from_sb(sb);

    max = range_IntSet( loop->def_var_list->array_bv );
    construct_IntSet( du_arr_bv, max );
    or_IntSet( du_arr_bv, def_arr_bv, use_arr_bv );

    for (i = 1; i < max; i++) {
        if (in_IntSet(du_arr_bv, i)) {
            for (apt = loop->dep_array; apt != NULL; apt = apt->next) {
                if (apt->entry == i && apt->dd_vec->sign == ASTER) {
                    remove1_IntSet(du_arr_bv, i);
                }
            }
        }
    }

    for( i = 1; i < max; i++ ){
	if( in_IntSet(du_arr_bv, i) ){

	    dep_arr = alloc_depend_array();
        dep_arr->kind = KIND_ARRAY;
	    dep_arr->entry = i;
	    dep_arr->def_opt = NULL;
	    dep_arr->use_opt = NULL;
            dep_arr->def_sub_id_ptr = NULL;
            dep_arr->use_sub_id_ptr = NULL;
            dep_arr->def_stm = call_stm;
            dep_arr->use_stm = call_stm;
	    dep_arr->indep = FALSE;
	    dep_arr->dd_vec->tag = FALSE;
	    dep_arr->dd_vec->value = -1;
	    dep_arr->dd_vec->sign = ASTER;

	    if( loop->dep_array ){
		for( apt = loop->dep_array; apt->next; apt = apt->next );
		apt->next = dep_arr;
	    }else
		loop->dep_array = dep_arr;
	}
    }
    destruct_IntSet(du_arr_bv);
}
