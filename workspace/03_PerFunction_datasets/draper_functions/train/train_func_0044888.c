gf_fuse_unmount (const char *mountpoint, int fd)
{
        int res;
        int pid;

        if (!mountpoint)
                return;

        if (fd != -1) {
                struct pollfd pfd;

                pfd.fd = fd;
                pfd.events = 0;
                res = poll (&pfd, 1, 0);


                if (res == 1 && (pfd.revents & POLLERR))
                        return;


                close (fd);
        }

        if (geteuid () == 0) {
                fuse_mnt_umount ("fuse", mountpoint, mountpoint, 1);
                return;
        }

        res = umount2 (mountpoint, 2);
        if (res == 0)
                return;

        pid = fork ();
        if (pid == -1)
                return;

        if (pid == 0) {
                const char *argv[] = { FUSERMOUNT_PROG, "-u", "-q", "-z",
                                       "--", mountpoint, NULL };

                execvp (FUSERMOUNT_PROG, (char **)argv);
                _exit (1);
        }
        waitpid (pid, NULL, 0);
}
