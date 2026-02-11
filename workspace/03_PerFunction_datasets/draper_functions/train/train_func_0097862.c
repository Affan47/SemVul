startProcessInternal(int argc, const char *argv[], bool waitAndExit, bool directly)
{
    fprintf(stderr, "KCrash: Attempting to start %s %s\n", argv[0], directly ? "directly" : "from kdeinit");

    pid_t pid = directly ? startDirectly(argv) : startFromKdeinit(argc, argv);

    if (pid > 0 && waitAndExit) {

        alarm(0);


        if (directly) {

            while(waitpid(-1, NULL, 0) != pid) {}
        } else {
#ifdef Q_OS_LINUX

#ifndef PR_SET_PTRACER
# define PR_SET_PTRACER 0x59616d61
#endif
            prctl(PR_SET_PTRACER, pid, 0, 0, 0);
#endif

            while(kill(pid, 0) >= 0) {
                sleep(1);
            }
        }


    }

    return (pid > 0);
}
