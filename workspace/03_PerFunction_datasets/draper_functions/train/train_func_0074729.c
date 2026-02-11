us_socket_collection_close_plain_socket( us_socket_collection_t *self, int fd, void *socket_context )
{
    if ( fd != -1 )
    {
        (void)socket_context;
        closesocket( fd );
        us_socket_collection_remove_fd( self, fd );
    }
}
