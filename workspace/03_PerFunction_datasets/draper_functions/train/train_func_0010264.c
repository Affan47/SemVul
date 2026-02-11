sge_rx_timer_cb(unsigned long data)
{
	unsigned long m;
	unsigned int i;
	struct adapter *adap = (struct adapter *)data;
	struct sge *s = &adap->sge;

	for (i = 0; i < BITS_TO_LONGS(s->egr_sz); i++)
		for (m = s->starving_fl[i]; m; m &= m - 1) {
			struct sge_eth_rxq *rxq;
			unsigned int id = __ffs(m) + i * BITS_PER_LONG;
			struct sge_fl *fl = s->egr_map[id];

			clear_bit(id, s->starving_fl);
			smp_mb__after_atomic();

			if (fl_starving(adap, fl)) {
				rxq = container_of(fl, struct sge_eth_rxq, fl);
				if (napi_reschedule(&rxq->rspq.napi))
					fl->starving++;
				else
					set_bit(id, s->starving_fl);
			}
		}


	if (!(adap->flags & MASTER_PF))
		goto done;

	t4_idma_monitor(adap, &s->idma_monitor, HZ, RX_QCHECK_PERIOD);

done:
	mod_timer(&s->rx_timer, jiffies + RX_QCHECK_PERIOD);
}
