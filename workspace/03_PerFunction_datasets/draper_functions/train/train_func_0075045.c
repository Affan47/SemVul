runProgram(const char *path, const char *const *args) {
    flushXEvents();

    int cpid = -1;
    if (path && (cpid = fork()) == 0) {
        app->resetSignals();
        sigemptyset(&signalMask);
        sigaddset(&signalMask, SIGHUP);
        sigprocmask(SIG_UNBLOCK, &signalMask, NULL);


        setsid();
#if 0
        close(0);
        if (open("/dev/null", O_RDONLY) != 0)
            _exit(1);
#endif
        closeFiles();

        if (args)
            execvp(path, (char **)args);
        else
            execlp(path, path, (void *)NULL);

        _exit(99);
    }
    return cpid;
}
