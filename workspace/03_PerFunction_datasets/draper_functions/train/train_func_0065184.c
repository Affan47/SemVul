die_s_(const char *msg, const FLAC__StreamEncoder *encoder)
{
	FLAC__StreamEncoderState state = FLAC__stream_encoder_get_state(encoder);

	if(msg)
		printf("FAILED, %s", msg);
	else
		printf("FAILED");

	printf(", state = %u (%s)\n", (unsigned)state, FLAC__StreamEncoderStateString[state]);
	if(state == FLAC__STREAM_ENCODER_VERIFY_DECODER_ERROR) {
		FLAC__StreamDecoderState dstate = FLAC__stream_encoder_get_verify_decoder_state(encoder);
		printf("      verify decoder state = %u (%s)\n", (unsigned)dstate, FLAC__StreamDecoderStateString[dstate]);
	}

	return false;
}
