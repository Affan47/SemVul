handle_resynchronize(struct linked_server *ls,
                     const void *data __attr_unused,
                     size_t length __attr_unused)
{
    log(3, "Resync!\n");

    ls->connection->walk.seq_next = 0;

    return PA_ACCEPT;
}
