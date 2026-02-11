ReadHeader( string &headerT )
{
    headerT = "";

    string tempheader;
    ssize_t read;
    int received = 0;
    string::size_type position;


    for(;;)
    {
        read = SocketHandler::Recv( tempheader, false, -1 );

        if ( read < 1 )
        {
            return false;
        }

        received += read;

        if ( (position = tempheader.find_first_not_of("\r\n\t ")) != string::npos )
        {
            if ( position > 0 )
            {
                tempheader.erase( 0, position );

                read -= position;

                string ws;
                SocketHandler::RecvLength( ws, position );
            }


            break;
        }

        if ( received > MAXHTTPHEADERLENGTH )
        {
            LogFile::ErrorMessage("Too large header received (>%d)\n", MAXHTTPHEADERLENGTH);
            return false;
        }

        SocketHandler::RecvLength( tempheader, read );

        tempheader = "";
    }

    bool WrongHeader = false;
    int poscount = 0;

    while ( (position = tempheader.find("\r\n\r\n")) == string::npos )
    {

        if ( (position = tempheader.find("\n\n")) != string::npos )
        {
            WrongHeader = true;
            break;
        }


        if ( SocketHandler::RecvLength( headerT, read ) == false )
        {
            return false;
        }

        poscount += read;
        received += read;


        if ( received > MAXHTTPHEADERLENGTH )
        {
            LogFile::ErrorMessage("Too large header received (>%d)\n", MAXHTTPHEADERLENGTH);
            return false;
        }

        if ( (read = SocketHandler::Recv( tempheader, false, -1 )) < 1 )
        {

            if ( read == 0 && ( headerT.find_last_of( "\r\n" ) == headerT.size() - 1 ) )
            {
                return true;
            }

            return false;
        }
    }


    if ( SocketHandler::RecvLength( headerT, position - poscount + 2 ) == false )
    {
        return false;
    }

    if ( WrongHeader == false )
    {

        if ( SocketHandler::RecvLength( tempheader, 2 ) == false )
        {
            return false;
        }
    }

    return true;
}
