dump_rx_link_stats(struct rx_link_stats *rx)
{
	int i;

	faifa_printf(out_stream, "MPDU acked......................: %llu\n", (long long unsigned)(rx->mpdu_ack));
	faifa_printf(out_stream, "MPDU failures...................: %llu\n", (long long unsigned)(rx->mpdu_fail));
	faifa_printf(out_stream, "PB received successfully........: %llu\n", (long long unsigned)(rx->pb_passed));
	faifa_printf(out_stream, "PB received unsuccessfully......: %llu\n", (long long unsigned)(rx->pb_failed));
	faifa_printf(out_stream, "Turbo Bit Errors passed.........: %llu\n", (long long unsigned)(rx->tbe_passed));
	faifa_printf(out_stream, "Turbo Bit Errors failed.........: %llu\n", (long long unsigned)(rx->tbe_failed));

	for (i = 0; i < rx->num_rx_intervals; i++) {
		faifa_printf(out_stream, "-- Rx interval %d --\n", i);
		faifa_printf(out_stream, "Rx PHY rate.....................: %02d\n", (short unsigned int)(rx->rx_interval_stats[i].phyrate));
		faifa_printf(out_stream, "PB received successfully........: %llu\n", (long long unsigned)(rx->rx_interval_stats[i].pb_passed));
		faifa_printf(out_stream, "PB received failed..............: %llu\n", (long long unsigned)(rx->rx_interval_stats[i].pb_failed));
		faifa_printf(out_stream, "TBE errors over successfully....: %llu\n", (long long unsigned)(rx->rx_interval_stats[i].tbe_passed));
		faifa_printf(out_stream, "TBE errors over failed..........: %llu\n", (long long unsigned)(rx->rx_interval_stats[i].tbe_failed));
	}
}
