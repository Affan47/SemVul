jme_process_receive(struct jme_adapter *jme, int limit)
{
	struct jme_ring *rxring = &(jme->rxring[0]);
	struct rxdesc *rxdesc = rxring->desc;
	int i, j, ccnt, desccnt, mask = jme->rx_ring_mask;

	if (unlikely(!atomic_dec_and_test(&jme->rx_cleaning)))
		goto out_inc;

	if (unlikely(atomic_read(&jme->link_changing) != 1))
		goto out_inc;

	if (unlikely(!netif_carrier_ok(jme->dev)))
		goto out_inc;

	i = atomic_read(&rxring->next_to_clean);
	while (limit > 0) {
		rxdesc = rxring->desc;
		rxdesc += i;

		if ((rxdesc->descwb.flags & cpu_to_le16(RXWBFLAG_OWN)) ||
		!(rxdesc->descwb.desccnt & RXWBDCNT_WBCPL))
			goto out;
		--limit;

		rmb();
		desccnt = rxdesc->descwb.desccnt & RXWBDCNT_DCNT;

		if (unlikely(desccnt > 1 ||
		rxdesc->descwb.errstat & RXWBERR_ALLERR)) {

			if (rxdesc->descwb.errstat & RXWBERR_CRCERR)
				++(NET_STAT(jme).rx_crc_errors);
			else if (rxdesc->descwb.errstat & RXWBERR_OVERUN)
				++(NET_STAT(jme).rx_fifo_errors);
			else
				++(NET_STAT(jme).rx_errors);

			if (desccnt > 1)
				limit -= desccnt - 1;

			for (j = i, ccnt = desccnt ; ccnt-- ; ) {
				jme_set_clean_rxdesc(jme, j);
				j = (j + 1) & (mask);
			}

		} else {
			jme_alloc_and_feed_skb(jme, i);
		}

		i = (i + desccnt) & (mask);
	}

out:
	atomic_set(&rxring->next_to_clean, i);

out_inc:
	atomic_inc(&jme->rx_cleaning);

	return limit > 0 ? limit : 0;

}
