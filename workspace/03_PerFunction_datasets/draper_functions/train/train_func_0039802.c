mpi_task_make_recv_nt_set_list(Module_table *module)
{
    Mtg_table *mtg;
    Hmdf_table *hmdf;
    Block *block;
    List *list = NULL;

    for( mtg = mtg_head; mtg != NULL; mtg = mtg->next){
	hmdf = get_hmdf_table_from_id(mtg->mtg_id);
	if( hmdf->block->module == module){
	    for( block = hmdf->block->inner; block != NULL; block = block->next){
		if( block->recv_nt_set != NULL && list_find(list, block->recv_nt_set) == NULL){
		    list = list_append(list, block->recv_nt_set);
		}
		if( opt_tlg_loop_share_car_only && block->car_tag != -1){
		    if( block->send_nt_set != NULL && list_find(list, block->send_nt_set) == NULL){
			list = list_append(list, block->send_nt_set);
		    }
		}
	    }
	}
    }

    list = mpi_task_make_nt_set_in_pg_list_for_blocks(list, module->block_head);

    return list;
}
