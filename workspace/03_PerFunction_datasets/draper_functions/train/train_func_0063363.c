us_daemon_end(void)
{
    close( us_daemon_pid_fd );
    if( strlen(us_daemon_pid_file_name)>0 )
    {
        if( unlink( us_daemon_pid_file_name )<0 )
        {
            us_log_error("remove pid file failed: %s", strerror(errno));
        }
    }
}
