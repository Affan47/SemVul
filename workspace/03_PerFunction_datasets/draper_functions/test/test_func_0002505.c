ompfbe_ddsche_write_init_cx(fsbe_context *cx, Hmdf_table *hmdf)
{
    Hmdf_context *hcx = get_current_hmdf_context(hmdf);

    if( opt_mpi_task_code){
	if( hcx->pc_number == 0 && hcx->pe_number == 0)
	    ompfbe_mpi_task_write_init_call(cx, hcx->mtg_id);
	return;
    }

    if (opt_scheduler_module) {
        ddsche_write_init_call(cx, hcx);
    } else {
        if (hcx->pc_number == 0 && hcx->pe_number == 0) {
            ddsche_write_init_master(cx, hcx);
        } else {
            ddsche_write_init_slave(cx, hcx);
        }
    }
}
