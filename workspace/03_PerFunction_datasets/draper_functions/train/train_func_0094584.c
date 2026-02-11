ndmchan_n_avail_record (struct ndmchan *ch, unsigned long size) {
	if (ch->end_ix == ch->beg_ix)
		ch->end_ix = ch->beg_ix = 0;

	if (ch->end_ix >= ch->data_size - size) {
		ndmchan_compress (ch);
	}
	return ch->data_size - ch->end_ix;
}
