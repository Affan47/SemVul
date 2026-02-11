pre_gdb () {
    int i = 0;
    if(l_socket) close(l_socket);
    for (i=3; i<=500; i++) close(i);
    kill(getpid(), SIGABRT);
}
