PrepareDirLists(channel_t *channel) {
channel_t *current_channel = channel;

	while ( current_channel ) {
		char *const path[] = { current_channel->datadir, NULL };

		current_channel->fts = fts_open(path, FTS_LOGICAL|FTS_NOCHDIR,  compare);
		if ( !current_channel->fts ) {
			LogError( "fts_open() error in %s line %d: %s\n", __FILE__, __LINE__, strerror(errno) );
			continue;
		}


		current_channel->ftsent = fts_read(current_channel->fts);
		if ( current_channel->ftsent )

			current_channel->ftsent->fts_number = 0;

		while ( current_channel->ftsent ) {


		 	if ( current_channel->ftsent->fts_info == FTS_ERR ||
				 current_channel->ftsent->fts_info == FTS_NS) {
				LogError( "fts_read() %s error in %s line %d: %s\n",
					current_channel->ftsent->fts_path, __FILE__, __LINE__, strerror(current_channel->ftsent->fts_errno) );
				continue;
			}
			if ( current_channel->ftsent->fts_info != FTS_F ) {
				current_channel->ftsent = fts_read(current_channel->fts);
				continue;
			}

			current_channel->ftsent->fts_number++;


			if ( current_channel->ftsent->fts_namelen == 19 && strncmp(current_channel->ftsent->fts_name, "nfcapd.", 7) == 0 )
				break;


			current_channel->ftsent = fts_read(current_channel->fts);
		}
		current_channel = current_channel->next;
	}

}
