g15daemon_usleep(int useconds) {

    struct timeval timeout;
    if(useconds < 10000)
      useconds = 10000;
    timeout.tv_sec = useconds / 1000000;
    timeout.tv_usec = useconds % 1000000;
    return select (0,0,0,0,&timeout);
}
