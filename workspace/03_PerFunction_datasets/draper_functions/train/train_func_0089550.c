us_socket_collection_group_handle_sets( us_socket_collection_group_t *self,
                                             fd_set const *readable,
                                             fd_set const *writable,
                                             uint64_t current_time_in_ms )
{
    int i;
    for ( i = 0; i < self->num_collections; ++i )
    {
        us_socket_collection_t *c = self->collection[i];
        us_socket_collection_handle_readable_set( c, readable, current_time_in_ms );
        us_socket_collection_handle_writable_set( c, writable, current_time_in_ms );
        us_socket_collection_cleanup( c );
    }
}
