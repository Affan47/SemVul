block_until_new_connection(void) {
    struct timeval Timeout;
    fd_set readfs;
    int cycles;
    int i;

    LOG(llevInfo, "Waiting for connections...\n");

    cycles = 1;
    do {


        cycles++;
        if (cycles%2 == 0)
            tick_the_clock();

        FD_ZERO(&readfs);
        for (i = 0; i < socket_info.allocated_sockets && init_sockets[i].listen; i++)
            if (init_sockets[i].status == Ns_Add)
                FD_SET((uint32)init_sockets[i].fd, &readfs);


        if (settings.fastclock > 0) {
#ifdef WATCHDOG
            if (cycles%120000 == 0) {
                watchdog();
                flush_old_maps();
            }
#endif
            if (cycles == 720000) {
                metaserver_update();
                cycles = 1;
            }
            Timeout.tv_sec = 0;
            Timeout.tv_usec = 50;
        } else {
            Timeout.tv_sec = 60;
            Timeout.tv_usec = 0;
            if (cycles == 7) {
                metaserver_update();
                cycles = 1;
            }
            flush_old_maps();
        }
    } while (select(socket_info.max_filedescriptor, &readfs, NULL, NULL, &Timeout) == 0);

    reset_sleep();
}
