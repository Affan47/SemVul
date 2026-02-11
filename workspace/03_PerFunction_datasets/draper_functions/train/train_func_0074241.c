hdlc_irq(struct fritz_adapter *adapter)
{
	int nr;
	u32 stat;

	for (nr = 0; nr < 2; nr++) {
		stat = adapter->read_hdlc_status(adapter, nr);
		DBG(0x10, "HDLC %c stat %#x", 'A' + nr, stat);
		if (stat & HDLC_INT_MASK)
			hdlc_irq_one(&adapter->bcs[nr], stat);
	}
}
