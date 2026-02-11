us_socket_collection_remove_fd( us_socket_collection_t *self, int fd )
{
    bool r = false;
    int i;
    for ( i = 0; i < self->num_sockets; ++i )
    {
        if ( fd == self->socket_fd[i] )
        {
            self->socket_fd[i] = -1;
        }
    }
    return r;
}
