http_skip_chunk_crlf(struct http_msg *msg)
{
	const struct buffer *buf = msg->chn->buf;
	const char *ptr;
	int bytes;


	bytes = 1;
	ptr = b_ptr(buf, msg->next);
	if (*ptr == '\r') {
		bytes++;
		ptr++;
		if (ptr >= buf->data + buf->size)
			ptr = buf->data;
	}

	if (msg->next + bytes > buf->i)
		return 0;

	if (*ptr != '\n') {
		msg->err_pos = buffer_count(buf, buf->p, ptr);
		return -1;
	}

	ptr++;
	if (unlikely(ptr >= buf->data + buf->size))
		ptr = buf->data;

	msg->next += bytes;
	msg->msg_state = HTTP_MSG_CHUNK_SIZE;
	return 1;
}
