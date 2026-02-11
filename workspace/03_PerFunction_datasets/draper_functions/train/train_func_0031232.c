add_socket_to_parent(ioa_socket_handle parent_s, ioa_socket_handle s)
{
	if(parent_s && s) {
		delete_socket_from_parent(s);
		s->parent_s = parent_s;
		s->fd = parent_s->fd;
	}
}
