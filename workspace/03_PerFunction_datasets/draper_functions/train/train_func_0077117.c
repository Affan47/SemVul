podcast_item_new(void) {

	podcast_item_t * item;

	if ((item = (podcast_item_t *)calloc(1, sizeof(podcast_item_t))) == NULL) {
		fprintf(stderr, "podcast_item_new: calloc error\n");
		return NULL;
	}

	item->new = 1;
	item->size = 0;
	item->date = 0;
	item->duration = 0.0f;

	return item;
}
