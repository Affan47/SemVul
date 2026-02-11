operator= (  const TcpSocket &    ss )   throw ( Exception )
{
    if ( this != &ss ) {
        int     fd;


        strip();


        Sink::operator=( ss );
        Source::operator=( ss );

        init( ss.host, ss.port);

        if ( (fd = ss.sockfd ? dup( ss.sockfd) : 0) == -1 ) {
            strip();
            throw Exception( __FILE__, __LINE__, "dup failure");
        }

        sockfd = fd;
    }

    return *this;
}
