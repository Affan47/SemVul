gbhw_setbuffer(struct gbhw_buffer *buffer)
{
	soundbuf = buffer;
	soundbuf->samples = soundbuf->bytes / 4;

	if (impbuf) free(impbuf);
	impbuf = malloc(sizeof(*impbuf) + (soundbuf->samples + IMPULSE_WIDTH + 1) * 4);
	if (impbuf == NULL) {
		fprintf(stderr, "%s", _("Memory allocation failed!\n"));
		return;
	}
	memset(impbuf, 0, sizeof(*impbuf));
	impbuf->data = (void*)(impbuf+1);
	impbuf->samples = soundbuf->samples + IMPULSE_WIDTH + 1;
	impbuf->bytes = impbuf->samples * 4;
	gbhw_impbuf_reset(impbuf);
}
