handle_getoption(struct ast_channel *chan, AGI *agi, int argc, const char * const argv[])
{
	int res;
	struct ast_filestream *fs, *vfs;
	long sample_offset = 0, max_length;
	int timeout = 0;
	const char *edigits = "";

	if ( argc < 4 || argc > 5 )
		return RESULT_SHOWUSAGE;

	if ( argv[3] )
		edigits = argv[3];

	if ( argc == 5 )
		timeout = atoi(argv[4]);
	else if (ast_channel_pbx(chan)->dtimeoutms) {

		timeout = ast_channel_pbx(chan)->dtimeoutms;
	}

	if (!(fs = ast_openstream(chan, argv[2], ast_channel_language(chan)))) {
		ast_agi_send(agi->fd, chan, "200 result=-1 endpos=%ld\n", sample_offset);
		ast_log(LOG_WARNING, "Unable to open %s\n", argv[2]);
		return RESULT_FAILURE;
	}

	if ((vfs = ast_openvstream(chan, argv[2], ast_channel_language(chan))))
		ast_debug(1, "Ooh, found a video stream, too\n");

	ast_verb(3, "Playing '%s' (escape_digits=%s) (timeout %d)\n", argv[2], edigits, timeout);

	ast_seekstream(fs, 0, SEEK_END);
	max_length = ast_tellstream(fs);
	ast_seekstream(fs, sample_offset, SEEK_SET);
	res = ast_applystream(chan, fs);
	if (vfs)
		ast_applystream(chan, vfs);
	ast_playstream(fs);
	if (vfs)
		ast_playstream(vfs);

	res = ast_waitstream_full(chan, argv[3], agi->audio, agi->ctrl);


	sample_offset = (ast_channel_stream(chan))?ast_tellstream(fs):max_length;
	ast_stopstream(chan);
	if (res == 1) {

		return RESULT_SUCCESS;
	}


	if (res == 0 ) {
		res = ast_waitfordigit_full(chan, timeout, agi->audio, agi->ctrl);

		if ( !strchr(edigits,res) )
			res=0;
	}

	ast_agi_send(agi->fd, chan, "200 result=%d endpos=%ld\n", res, sample_offset);
	return (res >= 0) ? RESULT_SUCCESS : RESULT_FAILURE;
}
