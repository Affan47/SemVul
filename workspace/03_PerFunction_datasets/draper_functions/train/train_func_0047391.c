s2io_isr(int irq, void *dev_id)
{
	struct net_device *dev = (struct net_device *)dev_id;
	struct s2io_nic *sp = netdev_priv(dev);
	struct XENA_dev_config __iomem *bar0 = sp->bar0;
	int i;
	u64 reason = 0;
	struct mac_info *mac_control;
	struct config_param *config;


	if (pci_channel_offline(sp->pdev))
		return IRQ_NONE;

	if (!is_s2io_card_up(sp))
		return IRQ_NONE;

	config = &sp->config;
	mac_control = &sp->mac_control;


	reason = readq(&bar0->general_int_status);

	if (unlikely(reason == S2IO_MINUS_ONE))
		return IRQ_HANDLED;

	if (reason &
	    (GEN_INTR_RXTRAFFIC | GEN_INTR_TXTRAFFIC | GEN_INTR_TXPIC)) {
		writeq(S2IO_MINUS_ONE, &bar0->general_int_mask);

		if (config->napi) {
			if (reason & GEN_INTR_RXTRAFFIC) {
				napi_schedule(&sp->napi);
				writeq(S2IO_MINUS_ONE, &bar0->rx_traffic_mask);
				writeq(S2IO_MINUS_ONE, &bar0->rx_traffic_int);
				readl(&bar0->rx_traffic_int);
			}
		} else {


			if (reason & GEN_INTR_RXTRAFFIC)
				writeq(S2IO_MINUS_ONE, &bar0->rx_traffic_int);

			for (i = 0; i < config->rx_ring_num; i++) {
				struct ring_info *ring = &mac_control->rings[i];

				rx_intr_handler(ring, 0);
			}
		}


		if (reason & GEN_INTR_TXTRAFFIC)
			writeq(S2IO_MINUS_ONE, &bar0->tx_traffic_int);

		for (i = 0; i < config->tx_fifo_num; i++)
			tx_intr_handler(&mac_control->fifos[i]);

		if (reason & GEN_INTR_TXPIC)
			s2io_txpic_intr_handle(sp);


		if (!config->napi) {
			for (i = 0; i < config->rx_ring_num; i++) {
				struct ring_info *ring = &mac_control->rings[i];

				s2io_chk_rx_buffers(sp, ring);
			}
		}
		writeq(sp->general_int_mask, &bar0->general_int_mask);
		readl(&bar0->general_int_status);

		return IRQ_HANDLED;

	} else if (!reason) {

		return IRQ_NONE;
	}

	return IRQ_HANDLED;
}
