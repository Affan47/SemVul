wait4child( int sig )
{
    int save_errno = errno;

#ifdef WNOHANG
    do
        errno = 0;
#ifdef HAVE_WAITPID
    while ( waitpid( (pid_t)-1, NULL, WNOHANG ) > 0 || errno == EINTR );
#else
    while ( wait3( NULL, WNOHANG, NULL ) > 0 || errno == EINTR );
#endif
#else
    (void) wait( NULL );
#endif
    (void) SIGNAL_REINSTALL( sig, wait4child );
    errno = save_errno;
}
