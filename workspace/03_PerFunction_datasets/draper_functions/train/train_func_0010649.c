mpicbe_debug_info_elem( csbe_context *cx,
			Module_table *module,
			Nt_elem *nt_elem,
			Array_range_semnode **range,
			const char *send_or_recv )
{
    if(opt_mpi_debug_message){
        int i;
        Array_table *array = nt_elem->data.a;

        csbe_printf(cx, "MPI_Comm_rank(MPI_COMM_WORLD, &oscar_rank);\n");
        csbe_printf(cx, "fprintf(stdout,\"rank%%d: %s_elem%d ", send_or_recv, nt_elem->entry);
        csbe_write_array_name(cx, array);
        for (i = 0; i < array->dim; i++) {
            csbe_printf(cx, "[%%d:%%d]");
        }
        csbe_printf(cx, "\\n\",oscar_rank,");

        for( i = array->dim; i > 0; i--){
            mpi_task_write_semtree(cx, module, range[i-1]->lower_tree, array->bas.ct[i-1]);
            if (lang_tag == LANG_FORTRAN) csbe_printf(cx, "-1");
            csbe_printf(cx, ",");
            mpi_task_write_semtree(cx, module, range[i-1]->upper_tree, array->bas.ct[i-1]);
            if (lang_tag == LANG_FORTRAN) csbe_printf(cx, "-1");
            if (i - 1 > 0)
                csbe_printf(cx, ",");
        }
        csbe_printf(cx, ");");
        csbe_printf(cx, "fflush(stdout);\n");
    }
}
