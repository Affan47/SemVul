pnp_printf(pnp_info_buffer_t * buffer, char *fmt, ...)
{
	va_list args;
	int res;

	if (buffer->stop || buffer->error)
		return 0;
	va_start(args, fmt);
	res = vsnprintf(buffer->curr, buffer->len - buffer->size, fmt, args);
	va_end(args);
	if (buffer->size + res >= buffer->len) {
		buffer->stop = 1;
		return 0;
	}
	buffer->curr += res;
	buffer->size += res;
	return res;
}
