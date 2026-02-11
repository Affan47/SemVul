sring_read(sring_buffer *buf, char *dst, int dst_len)
{
	if (buf == NULL || dst == NULL || dst_len <= 0)
		return -1;


	if (dst_len > sring_getMaxRead(buf))
		dst_len = sring_getMaxRead(buf);

	if (buf->r + dst_len < buf->size) {
		memcpy(dst, buf->data + buf->r, dst_len);
		buf->r += dst_len;
	}
	else {
		int firstBlockLen = buf->size - buf->r;
		int secondBlockLen = dst_len - firstBlockLen;

		memcpy(dst, buf->data + buf->r, firstBlockLen);

		if (secondBlockLen > 0)
			memcpy(dst + firstBlockLen, buf->data, secondBlockLen);

		buf->r = secondBlockLen;
	}

	return dst_len;
}
