efx_test_loopback(struct efx_tx_queue *tx_queue,
		  struct efx_loopback_self_tests *lb_tests)
{
	struct efx_nic *efx = tx_queue->efx;
	struct efx_loopback_state *state = efx->loopback_selftest;
	int i, begin_rc, end_rc;

	for (i = 0; i < 3; i++) {

		state->packet_count = efx->txq_entries / 3;
		state->packet_count = min(1 << (i << 2), state->packet_count);
		state->skbs = kcalloc(state->packet_count,
				      sizeof(state->skbs[0]), GFP_KERNEL);
		if (!state->skbs)
			return -ENOMEM;
		state->flush = false;

		netif_dbg(efx, drv, efx->net_dev,
			  "TX queue %d testing %s loopback with %d packets\n",
			  tx_queue->queue, LOOPBACK_MODE(efx),
			  state->packet_count);

		efx_iterate_state(efx);
		begin_rc = efx_begin_loopback(tx_queue);


		msleep(1);
		if (!efx_poll_loopback(efx)) {
			msleep(LOOPBACK_TIMEOUT_MS);
			efx_poll_loopback(efx);
		}

		end_rc = efx_end_loopback(tx_queue, lb_tests);
		kfree(state->skbs);

		if (begin_rc || end_rc) {


			schedule_timeout_uninterruptible(HZ / 10);
			return begin_rc ? begin_rc : end_rc;
		}
	}

	netif_dbg(efx, drv, efx->net_dev,
		  "TX queue %d passed %s loopback test with a burst length "
		  "of %d packets\n", tx_queue->queue, LOOPBACK_MODE(efx),
		  state->packet_count);

	return 0;
}
