mpi_task_write_pg_comm_var_decl(fsbe_context *cx, Pe_in_pg *head)
{
    char name[64];
    Pe_in_pg *p;

    for( p = head; p != NULL; p = p->next){
        ompfbe_mpi_task_make_pg_comm_var_name(name, p->pe_num);
        ompfbe_iprintf(cx, "INTEGER %s\n", name);
    }
}
