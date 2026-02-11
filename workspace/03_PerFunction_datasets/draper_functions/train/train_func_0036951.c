main_loop(int listen_sockets[], int num_addr_listen)
{
    int in_socket, i, res;
    struct sigaction action;

    listener_pid_number = num_addr_listen;
    listener_pid = malloc(listener_pid_number * sizeof(listener_pid[0]));


    for (i = 0; i < num_addr_listen; i++) {
        if (!(listener_pid[i] = fork())) {


            while (1)
            {
                in_socket = accept(listen_sockets[i], 0, 0);
                if (verbose) fprintf(stderr, "accepted fd %d\n", in_socket);

                if (!fork())
                {
                    close(listen_sockets[i]);
                    start_shoveler(in_socket);
                    exit(0);
                }
                close(in_socket);
            }
        }
    }


    memset(&action, 0, sizeof(action));
    action.sa_handler = stop_listeners;
    res = sigaction(SIGTERM, &action, NULL);
    CHECK_RES_DIE(res, "sigaction");

    wait(NULL);
}
