dgnc_maxcps_room(struct tty_struct *tty, int bytes_available)
{
	struct channel_t *ch = NULL;
	struct un_t *un = NULL;

	if (!tty)
		return bytes_available;

	un = tty->driver_data;
	if (!un || un->magic != DGNC_UNIT_MAGIC)
		return bytes_available;

	ch = un->un_ch;
	if (!ch || ch->magic != DGNC_CHANNEL_MAGIC)
		return bytes_available;


	if (un->un_type != DGNC_PRINT)
		return bytes_available;

	if (ch->ch_digi.digi_maxcps > 0 && ch->ch_digi.digi_bufsize > 0) {
		int cps_limit = 0;
		unsigned long current_time = jiffies;
		unsigned long buffer_time = current_time +
			(HZ * ch->ch_digi.digi_bufsize) /
			ch->ch_digi.digi_maxcps;

		if (ch->ch_cpstime < current_time) {

			ch->ch_cpstime = current_time;
			cps_limit = ch->ch_digi.digi_bufsize;
		} else if (ch->ch_cpstime < buffer_time) {

			cps_limit = ((buffer_time - ch->ch_cpstime) *
					ch->ch_digi.digi_maxcps) / HZ;
		} else {

			cps_limit = 0;
		}

		bytes_available = min(cps_limit, bytes_available);
	}

	return bytes_available;
}
