SafeOpen(char *filename)

{ int fd;

#if defined HAVE_PTHREAD_H && (defined HAVE_LIBPTHREAD || defined BUILDTIN_GCC_THREAD)
 if (pthread_mutex_lock(&MUTEX_SYSCALL) != 0)
    {
    CfLog(cferror,"pthread_mutex_lock failed","pthread_mutex_lock");
    }
#endif

fd = open(filename,O_RDONLY);

#if defined HAVE_PTHREAD_H && (defined HAVE_LIBPTHREAD || defined BUILDTIN_GCC_THREAD)
 if (pthread_mutex_unlock(&MUTEX_SYSCALL) != 0)
    {
    CfLog(cferror,"pthread_mutex_unlock failed","pthread_mutex_unlock");
    }
#endif

return fd;
}
