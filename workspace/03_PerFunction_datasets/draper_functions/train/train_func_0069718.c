a3c90x_setup_rx_ring(struct INF_3C90X *p)
{
	int i;

	DBGP("a3c90x_setup_rx_ring\n");

	p->rx_ring =
	    malloc_dma(RX_RING_SIZE * sizeof(struct RXD), RX_RING_ALIGN);

	if (!p->rx_ring) {
		DBG("Could not allocate RX-ring\n");
		return -ENOMEM;
	}

	p->rx_cur = 0;

	for (i = 0; i < RX_RING_SIZE; i++) {
		p->rx_ring[i].UpNextPtr =
		    virt_to_bus(p->rx_ring + (i + 1));


		p->rx_ring[i].UpPktStatus = upComplete;
		p->rx_iobuf[i] = NULL;
	}


	p->rx_ring[i - 1].UpNextPtr = virt_to_bus(p->rx_ring);

	a3c90x_refill_rx_ring(p);

	return 0;
}
