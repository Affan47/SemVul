_sci1_sample_init(sci1_song_iterator_t *self, int offset)
{
	sci1_sample_t *sample, **seekerp;
	int rate;
	int length;
	int begin;
	int end;

	CHECK_FOR_END_ABSOLUTE(offset + 10);
	if (self->data[offset + 1] != 0)
		sciprintf("[iterator-1] In sample at offset 0x04x: Byte #1 is %02x instead of zero\n",
			  self->data[offset + 1]);

	rate = getInt16(self->data + offset + 2);
	length = getUInt16(self->data + offset + 4);
	begin = getInt16(self->data + offset + 6);
	end = getInt16(self->data + offset + 8);

	CHECK_FOR_END_ABSOLUTE(offset + 10 + length);

	sample = (sci1_sample_t*)sci_malloc(sizeof(sci1_sample_t));
	sample->delta = begin;
	sample->size = length;
	sample->data = self->data + offset + 10;

#ifdef DEBUG_VERBOSE
	fprintf(stderr, "[SAMPLE] %x/%x/%x/%x l=%x\n",
		offset + 10, begin, end, self->size, length);
#endif

	sample->format.format = SFX_PCM_FORMAT_U8;
	sample->format.stereo = SFX_PCM_MONO;
	sample->format.rate = rate;

	sample->announced = 0;


	seekerp = &(self->next_sample);

	while (*seekerp && (*seekerp)->delta < begin)
		seekerp = &((*seekerp)->next);

	sample->next = *seekerp;
	*seekerp = sample;

	return 0;
}
