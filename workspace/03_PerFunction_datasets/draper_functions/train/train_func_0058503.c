insert_dtu_store_local_array(Module_table *module,
			     Array_table *at,
			     Array_table *lm)
{
    Statement *head;
    Block *last_block;
    Statement *prev_stm = NULL, *stm;

    last_block = search_last_block(module->block_head->inner);

    head = make_stm_dtu_store_all_range(module,
					last_block,
					at,
					lm);

    for (stm = last_block->pre_head->stm_head; stm != NULL; stm = stm->next) {
	if (stm->ope == OPE_RETURN)
	    break;
	prev_stm = stm;
    }

    insert_stm(last_block->pre_head, prev_stm, head);

}
