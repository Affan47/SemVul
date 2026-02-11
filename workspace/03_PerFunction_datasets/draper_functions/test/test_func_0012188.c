new_fast_forward_iterator(song_iterator_t *capsit, int delta)
{
	fast_forward_song_iterator_t *it =
		(fast_forward_song_iterator_t*)sci_malloc(sizeof(fast_forward_song_iterator_t));

	if (capsit == NULL)
	{
	    free(it);
	    return NULL;
	}
	it->ID = 0;

	it->delegate = capsit;
	it->delta = delta;
	it->death_listeners_nr = 0;

	it->next = (int(*)(song_iterator_t *, unsigned char *, int *))
		_ff_read_next_command;
	it->get_pcm_feed = (sfx_pcm_feed_t *(*)(song_iterator_t *))
		_ff_check_pcm;
	it->handle_message = (song_iterator_t *(*)(song_iterator_t *,
						   song_iterator_message_t))
		_ff_handle_message;
	it->get_timepos = (int(*)(song_iterator_t *))_ff_get_timepos;
	it->init = (void(*)(song_iterator_t *))
		_ff_init;
	it->cleanup = NULL;
	it->channel_mask = capsit->channel_mask;


	return (song_iterator_t *) it;
}
