pkt_run_state_machine(struct pktcdvd_device *pd, struct packet_data *pkt)
{
	pkt_dbg(2, pd, "pkt %d\n", pkt->id);

	for (;;) {
		switch (pkt->state) {
		case PACKET_WAITING_STATE:
			if ((pkt->write_size < pkt->frames) && (pkt->sleep_time > 0))
				return;

			pkt->sleep_time = 0;
			pkt_gather_data(pd, pkt);
			pkt_set_state(pkt, PACKET_READ_WAIT_STATE);
			break;

		case PACKET_READ_WAIT_STATE:
			if (atomic_read(&pkt->io_wait) > 0)
				return;

			if (atomic_read(&pkt->io_errors) > 0) {
				pkt_set_state(pkt, PACKET_RECOVERY_STATE);
			} else {
				pkt_start_write(pd, pkt);
			}
			break;

		case PACKET_WRITE_WAIT_STATE:
			if (atomic_read(&pkt->io_wait) > 0)
				return;

			if (!pkt->w_bio->bi_error) {
				pkt_set_state(pkt, PACKET_FINISHED_STATE);
			} else {
				pkt_set_state(pkt, PACKET_RECOVERY_STATE);
			}
			break;

		case PACKET_RECOVERY_STATE:
			if (pkt_start_recovery(pkt)) {
				pkt_start_write(pd, pkt);
			} else {
				pkt_dbg(2, pd, "No recovery possible\n");
				pkt_set_state(pkt, PACKET_FINISHED_STATE);
			}
			break;

		case PACKET_FINISHED_STATE:
			pkt_finish_packet(pkt, pkt->w_bio->bi_error);
			return;

		default:
			BUG();
			break;
		}
	}
}
