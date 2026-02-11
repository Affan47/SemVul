ut_build_extra_ack(const struct ut_rmsg *um, struct ut_ack *ack)
{
	size_t first_missing, last_unacked;


	last_unacked = bit_array_last_set(um->facks, 0, um->fragcnt - 1);
	first_missing = bit_array_first_clear(um->fbits, 0, um->fragcnt - 1);


	if ((size_t) -1 == last_unacked) {
		last_unacked = (size_t) -1 == first_missing
			? um->fragcnt - 1U
			: bit_array_last_set(um->fbits, 0, um->fragcnt - 1);

		g_assert((size_t) -1 != last_unacked);
	}

	ZERO(ack);
	ack->seqno = um->id.seqno;

	if (um->improved_acks) {
		ut_cumulative_ack(um, ack, first_missing, last_unacked);
		ut_upgrade_ack(um, ack);
	} else {
		size_t last_frag = bit_array_last_set(um->fbits, 0, um->fragcnt - 1);
		g_assert((size_t) -1 != last_frag);
		ack->fragno = last_frag;
	}
}
