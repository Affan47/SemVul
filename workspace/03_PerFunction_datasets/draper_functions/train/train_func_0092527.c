a3c90x_free_rx_iobuf(struct INF_3C90X *p)
{
	int i;

	DBGP("a3c90x_free_rx_iobuf\n");

	for (i = 0; i < RX_RING_SIZE; i++) {
		free_iob(p->rx_iobuf[i]);
		p->rx_iobuf[i] = NULL;
	}
}
