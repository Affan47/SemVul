brasero_audio2cue_write (BraseroAudio2Cue *self,
			 int fd,
			 guchar *buffer,
			 gint bytes,
			 GError **error)
{
	gint bytes_remaining;
	gint bytes_written = 0;
	BraseroAudio2CuePrivate *priv;

	priv = BRASERO_AUDIO2CUE_PRIVATE (self);

	bytes_remaining = bytes;
	while (bytes_remaining) {
		gint written;

		written = write (fd,
				 buffer + bytes_written,
				 bytes_remaining);

		if (priv->cancel)
			return BRASERO_BURN_CANCEL;

		if (written != bytes_remaining) {
			if (errno != EINTR && errno != EAGAIN) {
                                int errsv = errno;


				g_set_error (error,
					     BRASERO_BURN_ERROR,
					     BRASERO_BURN_ERROR_GENERAL,
					     _("Data could not be written (%s)"),
					     g_strerror (errsv));
				return BRASERO_BURN_ERR;
			}
		}

		g_usleep (500);

		if (written > 0) {
			bytes_remaining -= written;
			bytes_written += written;
		}
	}

	return BRASERO_BURN_OK;
}
