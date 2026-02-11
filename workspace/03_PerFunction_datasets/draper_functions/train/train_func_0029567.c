start_logging(void)
{
#ifdef HAVE_WIN32_PROC
    char    temp[ MAX_PATH ];
    FILE*   fnul;
    FILE*   flog;

    GetTempPath( sizeof(temp) - 8, temp );
    strcat( temp, "adb.log" );


    fnul = fopen( "NUL", "rt" );
    if (fnul != NULL)
        stdin[0] = fnul[0];

    flog = fopen( temp, "at" );
    if (flog == NULL)
        flog = fnul;

    setvbuf( flog, NULL, _IONBF, 0 );

    stdout[0] = flog[0];
    stderr[0] = flog[0];
    fprintf(stderr,"--- adb starting (pid %d) ---\n", getpid());
#else
    int fd;

    fd = unix_open("/dev/null", O_RDONLY);
    dup2(fd, 0);
    adb_close(fd);

    fd = unix_open("/tmp/adb.log", O_WRONLY | O_CREAT | O_APPEND, 0640);
    if(fd < 0) {
        fd = unix_open("/dev/null", O_WRONLY);
    }
    dup2(fd, 1);
    dup2(fd, 2);
    adb_close(fd);
    fprintf(stderr,"--- adb starting (pid %d) ---\n", getpid());
#endif
}
