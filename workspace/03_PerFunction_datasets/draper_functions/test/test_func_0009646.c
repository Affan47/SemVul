spif_socket_comp(spif_socket_t self, spif_socket_t other)
{
    return SPIF_CMP_FROM_INT(self->fd - other->fd);
}
