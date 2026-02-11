us_socket_collection_destroy( us_socket_collection_t *self )
{
    int i;
    for ( i = 0; i < self->num_sockets; ++i )
    {
        int fd = self->socket_fd[i];
        self->close( self, fd, self->socket_context[i] );
    }
}
