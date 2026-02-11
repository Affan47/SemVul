sfx_iterator_make_feed(byte *base_data,
		       int offset,
		       int size,
		       sfx_pcm_config_t conf)
{
	sfx_pcm_feed_t *feed;
	pcm_data_internal_t *idat;
	byte *data = base_data + offset;

	if (!data) {

		return NULL;
	}
	sci_refcount_incref(base_data);

	idat = (pcm_data_internal_t*)sci_malloc(sizeof(pcm_data_internal_t));
	idat->base_data = base_data;
	idat->data = data;
	idat->frames_left = size;
	feed = (sfx_pcm_feed_t*)sci_malloc(sizeof(sfx_pcm_feed_t));
	*feed = pcm_it_prototype;
	feed->internal = idat;
	feed->conf = conf;

	return feed;
}
