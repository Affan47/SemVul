s2io_msix_fifo_handle(int irq, void *dev_id)
{
	int i;
	struct fifo_info *fifos = (struct fifo_info *)dev_id;
	struct s2io_nic *sp = fifos->nic;
	struct XENA_dev_config __iomem *bar0 = sp->bar0;
	struct config_param *config  = &sp->config;
	u64 reason;

	if (unlikely(!is_s2io_card_up(sp)))
		return IRQ_NONE;

	reason = readq(&bar0->general_int_status);
	if (unlikely(reason == S2IO_MINUS_ONE))

		return IRQ_HANDLED;

	if (reason & (GEN_INTR_TXPIC | GEN_INTR_TXTRAFFIC)) {
		writeq(S2IO_MINUS_ONE, &bar0->general_int_mask);

		if (reason & GEN_INTR_TXPIC)
			s2io_txpic_intr_handle(sp);

		if (reason & GEN_INTR_TXTRAFFIC)
			writeq(S2IO_MINUS_ONE, &bar0->tx_traffic_int);

		for (i = 0; i < config->tx_fifo_num; i++)
			tx_intr_handler(&fifos[i]);

		writeq(sp->general_int_mask, &bar0->general_int_mask);
		readl(&bar0->general_int_status);
		return IRQ_HANDLED;
	}

	return IRQ_NONE;
}
