track_init(void)
{
	Track *track = NULL;
	track = malloc(sizeof(Track));

	if (NULL == track) {
		fprintf(stderr, "unable to create track\n");
	} else {
		track->zero_pre.type = DATA_ZERO;
		track->zero_pre.name = NULL;
		track->zero_pre.start = 0;
		track->zero_pre.length = 0;

		track->file.type = DATA_AUDIO;
		track->file.name = NULL;
		track->file.start = 0;
		track->file.length = 0;

		track->zero_post.type = DATA_ZERO;
		track->zero_post.name = NULL;
		track->zero_post.start = 0;
		track->zero_post.length = 0;

		track->mode = MODE_AUDIO;
		track->sub_mode = SUB_MODE_RW;
		track->flags = FLAG_NONE;
		track->isrc = NULL;
		track->cdtext = cdtext_init();
		track->rem = rem_new();
		track->nindex = 0;
	}

	return track;
}
