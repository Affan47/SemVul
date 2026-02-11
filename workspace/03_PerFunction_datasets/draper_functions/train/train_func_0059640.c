r592_transfer_fifo_pio(struct r592_device *dev)
{
	unsigned long flags;

	bool is_write = dev->req->tpc >= MS_TPC_SET_RW_REG_ADRS;
	struct sg_mapping_iter miter;

	kfifo_reset(&dev->pio_fifo);

	if (!dev->req->long_data) {
		if (is_write) {
			r592_write_fifo_pio(dev, dev->req->data,
							dev->req->data_len);
			r592_flush_fifo_write(dev);
		} else
			r592_read_fifo_pio(dev, dev->req->data,
							dev->req->data_len);
		return 0;
	}

	local_irq_save(flags);
	sg_miter_start(&miter, &dev->req->sg, 1, SG_MITER_ATOMIC |
		(is_write ? SG_MITER_FROM_SG : SG_MITER_TO_SG));


	while (sg_miter_next(&miter))
		if (is_write)
			r592_write_fifo_pio(dev, miter.addr, miter.length);
		else
			r592_read_fifo_pio(dev, miter.addr, miter.length);


	if (is_write)
		r592_flush_fifo_write(dev);

	sg_miter_stop(&miter);
	local_irq_restore(flags);
	return 0;
}
