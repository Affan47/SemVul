xmms_wave_seek (xmms_xform_t *xform, gint64 samples,
                xmms_xform_seek_mode_t whence, xmms_error_t *error)
{
	xmms_wave_data_t *data;
	gint64 offset;
	gint64 ret;

	g_return_val_if_fail (xform, -1);
	g_return_val_if_fail (samples >= 0, -1);
	g_return_val_if_fail (whence == XMMS_XFORM_SEEK_SET, -1);

	data = xmms_xform_private_data_get (xform);
	g_return_val_if_fail (data, -1);


	offset = data->header_size;
	offset += samples * (data->bits_per_sample / 8) * data->channels;

	if (offset < data->header_size) {
		xmms_error_set (error, XMMS_ERROR_INVAL,
		                "Trying to seek before start of stream");
		return -1;
	}

	if (offset > data->header_size + data->bytes_total) {
		xmms_error_set (error, XMMS_ERROR_INVAL,
		                "Trying to seek past end of stream");
		return -1;
	}

	ret = xmms_xform_seek (xform, offset, whence, error);

	if (ret == -1) {
		return -1;
	}

	if (ret != offset) {
		XMMS_DBG ("xmms_xform_seek didn't return expected offset "
		          "(%" G_GINT64_FORMAT " != %" G_GINT64_FORMAT ")",
		          ret, offset);
	}

	ret -= data->header_size;

	ret /= (data->bits_per_sample / 8) * data->channels;

	return ret;
}
