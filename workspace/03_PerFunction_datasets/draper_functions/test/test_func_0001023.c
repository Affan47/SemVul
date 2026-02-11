via_ircc_hard_xmit_sir(struct sk_buff *skb,
						struct net_device *dev)
{
	struct via_ircc_cb *self;
	unsigned long flags;
	u16 iobase;
	__u32 speed;

	self = netdev_priv(dev);
	IRDA_ASSERT(self != NULL, return NETDEV_TX_OK;);
	iobase = self->io.fir_base;

	netif_stop_queue(dev);

	speed = irda_get_next_speed(skb);
	if ((speed != self->io.speed) && (speed != -1)) {

		if (!skb->len) {
			via_ircc_change_speed(self, speed);
			dev->trans_start = jiffies;
			dev_kfree_skb(skb);
			return NETDEV_TX_OK;
		} else
			self->new_speed = speed;
	}
	InitCard(iobase);
	CommonInit(iobase);
	SIRFilter(iobase, ON);
	SetSIR(iobase, ON);
	CRC16(iobase, ON);
	EnTXCRC(iobase, 0);
	WriteReg(iobase, I_ST_CT_0, 0x00);

	spin_lock_irqsave(&self->lock, flags);
	self->tx_buff.data = self->tx_buff.head;
	self->tx_buff.len =
	    async_wrap_skb(skb, self->tx_buff.data,
			   self->tx_buff.truesize);

	dev->stats.tx_bytes += self->tx_buff.len;

	SetBaudRate(iobase, self->io.speed);
	SetPulseWidth(iobase, 12);
	SetSendPreambleCount(iobase, 0);
	WriteReg(iobase, I_ST_CT_0, 0x80);

	EnableTX(iobase, ON);
	EnableRX(iobase, OFF);

	ResetChip(iobase, 0);
	ResetChip(iobase, 1);
	ResetChip(iobase, 2);
	ResetChip(iobase, 3);
	ResetChip(iobase, 4);

	EnAllInt(iobase, ON);
	EnTXDMA(iobase, ON);
	EnRXDMA(iobase, OFF);

	irda_setup_dma(self->io.dma, self->tx_buff_dma, self->tx_buff.len,
		       DMA_TX_MODE);

	SetSendByte(iobase, self->tx_buff.len);
	RXStart(iobase, OFF);
	TXStart(iobase, ON);

	dev->trans_start = jiffies;
	spin_unlock_irqrestore(&self->lock, flags);
	dev_kfree_skb(skb);
	return NETDEV_TX_OK;
}
