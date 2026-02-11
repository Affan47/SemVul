ompfbe_write_barrier(fsbe_context *cx, Hmdf_table *hmdf, int number)
{

    fsbe_printf(cx, "C @barrier_start:pe%d:module%d:no%d@\n",
                get_current_pe_number(), cx->module->entry, number);

    if(opt_mpi_task_code){
	ompfbe_mpi_task_write_barrier(cx, hmdf, number);
    }else{
	if(opt_barrier_flush)
	    ompfbe_write_flush(cx);

	switch (barrier_type) {
	case 1:
	case 2:
	case 3:
	case 4:
	    fatal("barrier_type 1-4 are obsolete\n");
	    break;
	case 5:
	case 6:
	    ompfbe_write_barrier_sub(cx, hmdf, number);
	    break;
	case 7:
	case 8:
	case 9:
	    fatal("barrier_type 7-9 are not out of maintenance.\n");
	    break;
	default:
	    fprintf(stderr, "Not expected barrier type.\n");
	    exit(1);
	}

	if(opt_barrier_flush)
	    ompfbe_write_flush(cx);
    }


    fsbe_printf(cx, "C @barrier_finish:pe%d:module%d:no%d@\n",
                get_current_pe_number(), cx->module->entry, number);

    return;
}
