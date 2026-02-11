verify_write_callback_(const FLAC__StreamDecoder *decoder, const FLAC__Frame *frame, const FLAC__int32 * const buffer[], void *client_data)
{
	FLAC__StreamEncoder *encoder = (FLAC__StreamEncoder *)client_data;
	unsigned channel;
	const unsigned channels = frame->header.channels;
	const unsigned blocksize = frame->header.blocksize;
	const unsigned bytes_per_block = sizeof(FLAC__int32) * blocksize;

	(void)decoder;

	for(channel = 0; channel < channels; channel++) {
		if(0 != memcmp(buffer[channel], encoder->private_->verify.input_fifo.data[channel], bytes_per_block)) {
			unsigned i, sample = 0;
			FLAC__int32 expect = 0, got = 0;

			for(i = 0; i < blocksize; i++) {
				if(buffer[channel][i] != encoder->private_->verify.input_fifo.data[channel][i]) {
					sample = i;
					expect = (FLAC__int32)encoder->private_->verify.input_fifo.data[channel][i];
					got = (FLAC__int32)buffer[channel][i];
					break;
				}
			}
			FLAC__ASSERT(i < blocksize);
			FLAC__ASSERT(frame->header.number_type == FLAC__FRAME_NUMBER_TYPE_SAMPLE_NUMBER);
			encoder->private_->verify.error_stats.absolute_sample = frame->header.number.sample_number + sample;
			encoder->private_->verify.error_stats.frame_number = (unsigned)(frame->header.number.sample_number / blocksize);
			encoder->private_->verify.error_stats.channel = channel;
			encoder->private_->verify.error_stats.sample = sample;
			encoder->private_->verify.error_stats.expected = expect;
			encoder->private_->verify.error_stats.got = got;
			encoder->protected_->state = FLAC__STREAM_ENCODER_VERIFY_MISMATCH_IN_AUDIO_DATA;
			return FLAC__STREAM_DECODER_WRITE_STATUS_ABORT;
		}
	}

	encoder->private_->verify.input_fifo.tail -= blocksize;
	FLAC__ASSERT(encoder->private_->verify.input_fifo.tail <= OVERREAD_);
	for(channel = 0; channel < channels; channel++)
		memmove(&encoder->private_->verify.input_fifo.data[channel][0], &encoder->private_->verify.input_fifo.data[channel][blocksize], encoder->private_->verify.input_fifo.tail * sizeof(encoder->private_->verify.input_fifo.data[0][0]));
	return FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE;
}
