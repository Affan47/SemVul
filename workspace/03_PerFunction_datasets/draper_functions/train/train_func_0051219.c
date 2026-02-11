EncoderSession_finish_error(EncoderSession *e)
{
	FLAC__ASSERT(e->encoder);

	if(e->total_samples_to_encode > 0)
		flac__utils_printf(stderr, 2, "\n");

	if(FLAC__stream_encoder_get_state(e->encoder) == FLAC__STREAM_ENCODER_VERIFY_MISMATCH_IN_AUDIO_DATA)
		print_verify_error(e);
	else if(e->outputfile_opened)

		flac_unlink(e->outfilename);

	EncoderSession_destroy(e);

	return 1;
}
