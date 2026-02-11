brasero_audio2cue_write_bin (BraseroAudio2Cue *self,
			     int fd_in,
			     int fd_out)
{
	BraseroAudio2CuePrivate *priv;

	priv = BRASERO_AUDIO2CUE_PRIVATE (self);

	while (1) {
		gint read_bytes;
		guchar buffer [2352 * 10];
		BraseroBurnResult result;

		read_bytes = brasero_audio2cue_read (self,
		                                     fd_in,
		                                     buffer,
		                                     sizeof (buffer),
		                                     &priv->error);


		if (read_bytes == -2)
			return BRASERO_BURN_CANCEL;

		if (read_bytes == -1) {
			int err_saved = errno;

			priv->error = g_error_new_literal (BRASERO_BURN_ERROR,
							   BRASERO_BURN_ERROR_GENERAL,
							   strerror (err_saved));
			return BRASERO_BURN_ERR;
		}

		if (!read_bytes)
			break;

		result = brasero_audio2cue_write (self,
		                                  fd_out,
		                                  buffer,
		                                  read_bytes,
		                                  &priv->error);
		if (result != BRASERO_BURN_OK)
			return result;

		priv->bytes += read_bytes;
	}

	return BRASERO_BURN_OK;
}
