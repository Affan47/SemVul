shutdown_atc(int signo) {
    if (shutting_down)
        return;
    shutting_down = true;
    msleep(100);
    kill(atc_pid, signo);
    msleep(100);
    write(ptm, "y", 1);
}
