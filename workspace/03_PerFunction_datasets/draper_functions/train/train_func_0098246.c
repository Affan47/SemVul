init_thread_server()
{
    int i;

    quit_count = 0;
    nmessage_count = 0;
    barrier_count = 0;
    master_barrier_msg_recvd = 0;

    MPI_Comm_size(newcomm, &nprocs);

    nactive = 0;
    nactive_pardo = 0;

    pardo_list_head = -1;
    pardo_list_tail = -1;

    init_msg_tag();

    for (i = 0; i < mbuffer; i++)
    {
       info[i].state = NullState;
       info[i].buffer = &recv_buffers[i*bsize];
    }

    for (i = 0; i < MAX_PARDO_MESSAGES; i++)
       pardo_info[i].state = NullState;
}
