dm_daemon_is_running(const char* lockfile)
{
       int fd;
       struct flock lock;

       if((fd = open(lockfile, O_RDONLY)) < 0)
               return 0;

       lock.l_type = F_WRLCK;
       lock.l_start = 0;
       lock.l_whence = SEEK_SET;
       lock.l_len = 0;
       if (fcntl(fd, F_GETLK, &lock) < 0) {
               log_error("Cannot check lock status of lockfile [%s], error was [%s]",
                         lockfile, strerror(errno));
               if (close(fd))
                       stack;
               return 0;
       }

       if (close(fd))
               stack;

       return (lock.l_type == F_UNLCK) ? 0 : 1;
}
