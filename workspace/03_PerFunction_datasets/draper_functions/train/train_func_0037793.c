ompfbe_mpi_task_write_send(fsbe_context *cx, Statement *sp, Quadruple *qp)
{
    int pe_no;
    int pe_num;
    char comm_name[64];
    Hmdf_table *hmdf;

    if(qp->op[0]->kind != KIND_SYNC){
	fprintf(stderr,"!!!!! ERROR illegal send: op[0]->kind is not SYNC\n");
	exit(3);
    }

    fsbe_printf(cx, "      ");
    sbe_write_operand(cx, qp->op[0]);
    fsbe_printf(cx, " = ");
    sbe_write_operand(cx, qp->op[1]);
    fsbe_printf(cx, "\n");

    pe_no = sp->pe_stm->vpe_no;
    hmdf = get_innermost_hmdf_table_of_outside(sp->pe_stm->block);
    pe_num = hmdf_pe_count(hmdf);
    ompfbe_mpi_task_make_pg_comm_var_name(comm_name, pe_num);

    if( pe_no == 0){
	ompfbe_iprintf(cx, "CALL MPI_BCAST( ");
	sbe_write_operand(cx, qp->op[0]);
	fsbe_printf(cx, ", 1, %s, 0, %s, OSCAR_MPI_IERR)\n", mpi_task_get_symbol_type_mpi_name(qp->op[0]->tbl.sync->type), comm_name);
    }else{
	ompfbe_iprintf(cx, "CALL MPI_SEND( ");
	sbe_write_operand(cx, qp->op[0]);
	fsbe_printf(cx, ", 1, %s, %d, 1, %s, OSCAR_MPI_IERR)\n", mpi_task_get_symbol_type_mpi_name(qp->op[0]->tbl.sync->type), qp->op[2]->entry, comm_name);
    }
}
