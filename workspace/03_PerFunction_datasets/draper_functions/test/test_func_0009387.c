mpicbe_write_synca(csbe_context *cx, Statement *stm, Quadruple *qr)
{
    char name[64];
    Hmdf_table *hmdf
	= get_innermost_hmdf_table_of_outside(stm->pe_stm->block);
    int pe_number = hmdf_current_pe_number_in_cluster(hmdf);
    int num_of_pe_in_cluster = hmdf_pe_count(hmdf);
    int barrier_count
	= ompfbe_get_barrier_number_synca(
	    qr->stm->pe_stm->block->module, qr, pe_number);

    if (verbose_level > 1) {
	fprintf(stderr, "pe%d: barrier_number (synca) = %d\n",
		pe_number, barrier_count);
    }

    csbe_printf(cx, "\n");
    if(!opt_barrier) return;
#if 0
    if(debug_barrier == 1
       || ( debug_barrier == 2
            && ompfbe_is_debug_barrier_module(cx->module))) {
        csbe_printf(cx, "WRITE(*,*) 'PE%d@%d: ENTER BARRIER%d', "
                       "BARRIER_FLG_%d_0_0, ' in %s'\n",
                       get_current_pe_number(),
                       pe_number,
                       barrier_count,
                       barrier_count,
                       cx->module->name);
    }
#endif
    ompfbe_mpi_task_make_pg_comm_var_name(name, num_of_pe_in_cluster);
    csbe_printf(cx, "OSCAR_MPI_IERR = MPI_Barrier(%s);\n", name);
#if 0
    if (debug_barrier == 1
        || ( debug_barrier == 2
             && ompfbe_is_debug_barrier_module(cx->module))) {
        csbe_printf(cx, "WRITE(*,*) 'PE%d@%d: %s: EXIT BARRIER%d', "
                       "BARRIER_FLG_%d_0_0, 'in %s'\n",
                       get_current_pe_number(),
                       pe_number,
                       cx->module->name,
                       barrier_count, barrier_count);
    }
#endif
    csbe_printf(cx, "\n");
    barrier_count++;
}
