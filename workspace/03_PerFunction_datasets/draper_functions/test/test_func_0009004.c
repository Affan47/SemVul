ndmchan_n_avail (struct ndmchan *ch) {
	if (ch->end_ix == ch->beg_ix)
		ch->end_ix = ch->beg_ix = 0;

	if (ch->end_ix >= ch->data_size) {
		ndmchan_compress (ch);
	}
	return ch->data_size - ch->end_ix;
}
