xmms_xform_this_peek (xmms_xform_t *xform, gpointer buf, gint siz,
                      xmms_error_t *err)
{
	while (xform->buffered < siz) {
		gint res;

		if (xform->buffered + READ_CHUNK > xform->buffersize) {
			xform->buffersize *= 2;
			xform->buffer = g_realloc (xform->buffer, xform->buffersize);
		}

		res = xmms_xform_plugin_read (xform->plugin, xform,
		                              &xform->buffer[xform->buffered],
		                              READ_CHUNK, err);

		if (res < -1) {
			XMMS_DBG ("Read method of %s returned bad value (%d) - BUG IN PLUGIN",
			          xmms_xform_shortname (xform), res);
			res = -1;
		}

		if (res == 0) {
			xform->eos = TRUE;
			break;
		} else if (res == -1) {
			xform->error = TRUE;
			return -1;
		} else {
			xform->buffered += res;
		}
	}


	siz = MIN (siz, xform->buffered);
	memcpy (buf, xform->buffer, siz);
	return siz;
}
