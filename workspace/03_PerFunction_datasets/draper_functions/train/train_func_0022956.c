cdda_unpack_func (void *v)
{
	cdimage_unpack_thread = 1;
	mp3decoder *mp3dec = NULL;

	for (;;) {
		uae_u32 cduidx = read_comm_pipe_u32_blocking (&unpack_pipe);
		if (cdimage_unpack_thread == 0)
			break;
		uae_u32 tocidx = read_comm_pipe_u32_blocking (&unpack_pipe);
		struct cdunit *cdu = &cdunits[cduidx];
		struct cdtoc *t = &cdu->toc[tocidx];
		if (t->handle) {

			uae_s64 pos = zfile_ftell (t->handle);
			zfile_fseek (t->handle, -1, SEEK_END);
			uae_u8 b;
			zfile_fread (&b, 1, 1, t->handle);
			zfile_fseek (t->handle, pos, SEEK_SET);
			if (!t->data && (t->enctype == AUDENC_MP3 || t->enctype == AUDENC_FLAC)) {
				t->data = xcalloc (uae_u8, t->filesize + 2352);
				cdimage_unpack_active = 1;
				if (t->data) {
					if (t->enctype == AUDENC_MP3) {
						if (!mp3dec) {
							try {
								mp3dec = new mp3decoder();
							} catch (exception) { };
						}
						if (mp3dec)
							t->data = mp3dec->get (t->handle, t->data, t->filesize);
					} else if (t->enctype == AUDENC_FLAC) {
						flac_get_data (t);
					}
				}
			}
		}
		cdimage_unpack_active = 2;
	}
	delete mp3dec;
	cdimage_unpack_thread = -1;
	return 0;
}
