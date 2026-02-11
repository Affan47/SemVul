seek_use_array_for_setting_array_list( Ic_array_table *array_list,
				       Block *loop, Block *bpt )
{
    Statement      *use_stm;
    Def_use_table  *use_array;
    int            dim;

    if( bpt->kind == BB || bpt->kind == BPA ){
	for( use_stm = bpt->pre_head->stm_head; use_stm;
	     use_stm = use_stm->next ){
	    for( use_array = use_stm->use_array_list; use_array;
		 use_array = use_array->next ){
		dim = count_array_dimention( get_loop_index_operand(loop)->entry,
					     get_loop_index_operand(loop)->kind,
					     use_array->sub_id_ptr );
		if( dim > -1 ){
		    set_array_list( array_list, use_array, dim );
		}
	    }
	}
    }
    if( bpt->inner != NULL )
	seek_use_array_for_setting_array_list( array_list, loop, bpt->inner);
    if( bpt->next != NULL )
	seek_use_array_for_setting_array_list( array_list, loop, bpt->next);
}
