Close()
{

    RecvBuf = "";


    if ( sock_fd > -1 )
    {
        while ( ::close(sock_fd) < 0 )
        {
            if (errno == EINTR) continue;
            if (errno == EBADF) break;


            LogFile::ErrorMessage("close() failed: %s\n", strerror(errno));
        }


        sock_fd = -1;
    }
}
