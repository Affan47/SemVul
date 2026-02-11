free_init_data(Module_table *mpt)
{
    int           i,bound_count;
    Common_table *cmpt;

    if(e_num > 0){
	free(eq_bd_cnt_list);
	eq_bd_cnt_list = NULL;

	free(eq_node_cnt_list);
	eq_node_cnt_list = NULL;

	for(cmpt = mpt->equiv_head, i = 0; cmpt != NULL;
	    cmpt = cmpt->next, i++){
	    bound_count = get_common_bound_count(cmpt->node_head);
	    if((bound_count > 0)&&(eq_bd_list[i] != NULL)){
		free(eq_bd_list[i]);
	    }
	}
	free(eq_bd_list);
	eq_bd_list = NULL;
    }
}
