it87_enable_tx_interrupt(struct ite_dev *dev)
{
	ite_dbg("%s called", __func__);


	outb(inb(dev->cir_addr + IT87_IER) | IT87_TLDLIE | IT87_IEC,
		dev->cir_addr + IT87_IER);
}
