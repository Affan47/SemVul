ndmchan_write_interpret (struct ndmchan *ch, char **data_p,
  unsigned *n_avail_p)
{
	unsigned	n_avail;

	n_avail = *n_avail_p = ndmchan_n_avail (ch);
	*data_p = &ch->data[ch->end_ix];

	if (ch->error) {

		return NDMCHAN_WI_DONE_ERROR;
	}

	if (ch->eof) {
		if (n_avail == ch->data_size) {
			return NDMCHAN_WI_DONE_EOF;
		} else {
			return NDMCHAN_WI_DRAIN_EOF;
		}
	}

	if (n_avail == 0) {
		return NDMCHAN_WI_FULL;
	}

	if (n_avail == ch->data_size) {
		return NDMCHAN_WI_AVAIL_EMPTY;
	}

	return NDMCHAN_WI_AVAIL;
}
