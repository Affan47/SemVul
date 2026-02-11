jme_free_rx_buf(struct jme_adapter *jme, int i)
{
	struct jme_ring *rxring = &jme->rxring;
	struct io_buffer *rxbi = rxring->bufinf[i];

	if (rxbi) {
		free_iob(rxbi);
		rxring->bufinf[i] = NULL;
	}
}
