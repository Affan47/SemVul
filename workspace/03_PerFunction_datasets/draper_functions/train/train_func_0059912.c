swf_soundstream_hdr(SWFReader *read)
{
	char szName[1024];
	SWFSound *snd;

	if (read->sound_stream) {
		swf_report(read, GF_BAD_PARAM, "More than one sound stream for current timeline!!");
		return swf_func_skip(read);
	}

	GF_SAFEALLOC(snd, SWFSound);

	swf_read_int(read, 8);

	snd->format = swf_read_int(read, 4);

	snd->sound_rate = swf_read_int(read, 2);

	snd->bits_per_sample = swf_read_int(read, 1) ? 16 : 8;

	snd->stereo = swf_read_int(read, 1);

	swf_read_int(read, 16);

	switch (snd->format) {

	case 0:
		swf_report(read, GF_NOT_SUPPORTED, "Raw PCM Audio not supported");
		gf_free(snd);
		break;

	case 1:
		swf_report(read, GF_NOT_SUPPORTED, "AD-PCM Audio not supported");
		gf_free(snd);
		break;

	case 2:
		read->sound_stream = snd;
		if (read->localPath) {
			sprintf(szName, "%s/swf_soundstream_%d.mp3", read->localPath, read->current_sprite_id);
		} else {
			sprintf(szName, "swf_soundstream_%d.mp3", read->current_sprite_id);
		}
		read->sound_stream->szFileName = gf_strdup(szName);
		read->setup_sound(read, read->sound_stream, 0);
		break;
	case 3:
		swf_report(read, GF_NOT_SUPPORTED, "Unrecognized sound format");
		gf_free(snd);
		break;
	}
	return GF_OK;
}
