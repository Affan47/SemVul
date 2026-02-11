_sci1_get_pcm(sci1_song_iterator_t *self)
{
	if (self->next_sample
	    && self->next_sample->delta <= 0) {
		sci1_sample_t *sample = self->next_sample;
		sfx_pcm_feed_t *feed
			= sfx_iterator_make_feed(self->data,
						 sample->data - self->data,
						 sample->size,
						 sample->format);

		self->next_sample = self->next_sample->next;

		sci_free(sample);

		return feed;
	} else
		return NULL;
}
