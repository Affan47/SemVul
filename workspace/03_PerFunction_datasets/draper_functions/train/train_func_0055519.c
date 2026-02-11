cmd_get_scanning_parameters(SANE_Handle handle,
			    SANE_Frame *format, SANE_Int *depth,
			    SANE_Int *data_pixels, SANE_Int *pixels_per_line,
			    SANE_Int *lines)
{
	Magicolor_Scanner *s = (Magicolor_Scanner *) handle;
	SANE_Status status;
	unsigned char *txbuf, rxbuf[8];
	size_t buflen;
	NOT_USED (format);
	NOT_USED (depth);

	DBG(8, "%s\n", __func__);
	buflen = mc_create_buffer (s, s->hw->cmd->scanner_cmd,
				   s->hw->cmd->request_scan_parameters,
				   &txbuf, NULL, 8, &status);
	if (buflen <= 0 ) {
		return SANE_STATUS_NO_MEM;
	} else if (status != SANE_STATUS_GOOD) {
		return status;
	}

	status = mc_txrx (s, txbuf, buflen, rxbuf, 8);
	free (txbuf);
	if (status != SANE_STATUS_GOOD)
		DBG(8, "%s: Parameters NOT successfully retrieved\n", __func__);
	else {
		DBG(8, "%s: Parameters successfully retrieved\n", __func__);


		if (rxbuf[2]!=rxbuf[6] || rxbuf[3]!=rxbuf[7]) {
			DBG (1, "%s: ERROR: Returned image parameters indicate an "
				"unsupported device: Bytes 3-4 do not match "
				"bytes 7-8! Trying to continue with bytes 3-4.\n",
				__func__);
			dump_hex_buffer_dense (1, rxbuf, 8);
		}

		*data_pixels = rxbuf[1] * 0x100 + rxbuf[0];
		*lines = rxbuf[3] * 0x100 + rxbuf[2];
		*pixels_per_line = rxbuf[5] * 0x100 + rxbuf[4];
		DBG (8, "%s: data_pixels = 0x%x (%u), lines = 0x%x (%u), "
		        "pixels_per_line = 0x%x (%u)\n", __func__,
		        *data_pixels, *data_pixels,
		        *lines, *lines,
		        *pixels_per_line, *pixels_per_line);
	}

	return status;
}
