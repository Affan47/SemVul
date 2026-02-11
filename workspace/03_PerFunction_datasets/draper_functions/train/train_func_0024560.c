ldns_bgetc(ldns_buffer *buffer)
{
	if (!ldns_buffer_available_at(buffer, buffer->_position, sizeof(uint8_t))) {
		ldns_buffer_set_position(buffer, ldns_buffer_limit(buffer));

		return EOF;
	}
	return (int)ldns_buffer_read_u8(buffer);
}
