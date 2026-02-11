ompfbe_mpi_task_search_inner_hmdf_for_module(Module_table *module)
{
    if( module->block_head->hmdf != NULL){
	return module->block_head->hmdf;
    }else{
	return mpi_task_search_inner_hmdf_for_block(module->block_head);
    }
}
