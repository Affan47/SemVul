mpicbe_task_write_gen_pg_comm(csbe_context *cx, int total_pe)
{
    char name[64];
    int i;
    int comm_num;
    Pe_in_pg *p;

    for( p = mpi_task_get_pg_comm_list(); p; p = p->next){
        comm_num = total_pe / p->pe_num;
        csbe_printf(cx, "for (i = 1; i <= %d; i++) {\n", comm_num);
        for( i = 0; i < p->pe_num; i++){
            csbe_printf(cx, "PG_RANKS[%d] = %d + (i - 1) * %d;\n", i, (i+1), p->pe_num);
        }
        csbe_printf(cx, "ierr = MPI_Group_incl(GROUP_WORLD, %d, PG_RANKS, &PG_GROUP);\n", p->pe_num);
        csbe_printf(cx, "ierr = MPI_Comm_create(MPI_COMM_WORLD, PG_GROUP, &PG_COMM);\n");
        csbe_printf(cx, "if (rank > (i - 1) * %d && rank <= i * %d) {\n", p->pe_num, p->pe_num);
        ompfbe_mpi_task_make_pg_comm_var_name(name, p->pe_num);
        csbe_printf(cx, "%s = PG_COMM;\n", name);
        csbe_printf(cx, "}\n");
        csbe_printf(cx, "}\n");
    }
}
