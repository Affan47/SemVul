pull_buffer_impl(
    XferElement *elt,
    size_t *size)
{
    XferSourceHolding *self = (XferSourceHolding *)elt;
    char *buf = NULL;
    size_t bytes_read;

    if (elt->cancelled)
	goto return_eof;

    if (self->fd == -1) {
	if (!start_new_chunk(self))
	    goto return_eof;
    }

    buf = g_malloc(HOLDING_BLOCK_SIZE);

    while (1) {
	bytes_read = full_read(self->fd, buf, HOLDING_BLOCK_SIZE);
	if (bytes_read > 0) {
	    *size = bytes_read;
	    self->bytes_read += bytes_read;
	    return buf;
	}


	if (errno != 0) {
	    xfer_cancel_with_error(XFER_ELEMENT(self),
		"while reading holding file: %s", strerror(errno));
	    wait_until_xfer_cancelled(XFER_ELEMENT(self)->xfer);
	    goto return_eof;
	}

	if (!start_new_chunk(self))
	    goto return_eof;
    }

return_eof:
    g_free(buf);
    *size = 0;
    return NULL;
}
