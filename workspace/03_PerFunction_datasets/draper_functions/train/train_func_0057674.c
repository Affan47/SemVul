msg_get_writeable_space( int size )
{
	if ( *msg_buf_cur_size + size > msg_buf_max_size ) {
		msg_write_overflow = 1;
		*msg_buf_cur_size = 0;
	}
	return msg_buf + *msg_buf_cur_size;
}
