msg_get_readable_space( int size )
{
	if ( msg_read_pos + size > net_buffer_cur_size ) {
		msg_read_exceeded = 1;
		msg_read_pos = 0;
	}
	return net_buffer + msg_read_pos;

}
