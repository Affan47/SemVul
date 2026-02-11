et131x_init_recv(struct et131x_adapter *adapter)
{
	struct rfd *rfd;
	u32 rfdct;
	struct rx_ring *rx_ring = &adapter->rx_ring;


	for (rfdct = 0; rfdct < rx_ring->num_rfd; rfdct++) {
		rfd = kzalloc(sizeof(*rfd), GFP_ATOMIC | GFP_DMA);
		if (!rfd)
			return -ENOMEM;

		rfd->skb = NULL;


		list_add_tail(&rfd->list_node, &rx_ring->recv_list);


		rx_ring->num_ready_recv++;
	}

	return 0;
}
