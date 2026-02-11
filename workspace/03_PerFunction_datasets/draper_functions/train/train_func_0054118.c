run ()
{
    while (true)
    {
        trigger_ev.timed_wait (30 * 1000);

        helpers::getLogLog().debug (
            DCMTK_LOG4CPLUS_TEXT("SocketAppender::ConnectorThread::run()")
            DCMTK_LOG4CPLUS_TEXT("- running..."));


        {
            thread::MutexGuard guard (access_mutex);
            if (exit_flag)
                return;
            trigger_ev.reset ();
        }


        {
            thread::MutexGuard guard (sa.access_mutex);
            if (sa.socket.isOpen ())
                continue;
        }


        helpers::Socket new_socket (sa.host,
            OFstatic_cast(unsigned short, sa.port));
        if (! new_socket.isOpen ())
        {
            helpers::getLogLog().error(
                DCMTK_LOG4CPLUS_TEXT("SocketAppender::ConnectorThread::run()")
                DCMTK_LOG4CPLUS_TEXT("- Cannot connect to server"));


            helpers::sleep (5);

            continue;
        }


        {
            thread::MutexGuard guard (sa.access_mutex);
            sa.socket = new_socket;
            sa.connected = true;
        }
    }
}
