MakeDaemon()
{
    pid_t daemon = fork();

    if ( daemon < 0 )
    {
        return false;
    }
    else if (daemon != 0)
    {

        exit(0);
    }


    setsid();
    chdir("/tmp/");
    umask(077);


    close(0);
    close(1);
    close(2);

    return true;
}
