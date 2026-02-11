mpi_task_write_gen_pg_comm(fsbe_context *cx, int total_pe)
{
    char name[64];
    int i;
    int comm_num;
    Pe_in_pg *p;
    Pe_in_pg *head;

    head = mpi_task_get_pg_comm_list();

    for( p = head; p != NULL; p = p->next){
        comm_num = total_pe / p->pe_num;
        ompfbe_iprintf(cx, "DO I=1,%d,1\n", comm_num);
        for( i = 1; i <= p->pe_num; i++){
            ompfbe_iprintf(cx, "PG_RANKS(%d) = %d + (I - 1) * %d\n", i, i, p->pe_num);
        }
        ompfbe_iprintf(cx, "CALL MPI_GROUP_INCL(GROUP_WORLD, %d, PG_RANKS, PG_GROUP, IERR)\n", p->pe_num);
        ompfbe_iprintf(cx, "CALL MPI_COMM_CREATE(MPI_COMM_WORLD, PG_GROUP, PG_COMM, IERR)\n");
        ompfbe_iprintf(cx, "IF((RANK .GT. ((I - 1) * %d)) .AND. (RANK .LE. (I * %d))) THEN\n", p->pe_num, p->pe_num);
        ompfbe_mpi_task_make_pg_comm_var_name(name, p->pe_num);
        ompfbe_iprintf(cx, "%s = PG_COMM\n", name);
        ompfbe_iprintf(cx, "END IF\n");
        ompfbe_iprintf(cx, "END DO\n\n");
    }
}
