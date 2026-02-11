tsi721_disable_ints(struct tsi721_device *priv)
{
	int ch;


	iowrite32(0, priv->regs + TSI721_DEV_INTE);


	iowrite32(0, priv->regs + TSI721_DEV_CHAN_INTE);


	for (ch = 0; ch < TSI721_IMSG_CHNUM; ch++)
		iowrite32(0, priv->regs + TSI721_IBDMAC_INTE(ch));


	for (ch = 0; ch < TSI721_OMSG_CHNUM; ch++)
		iowrite32(0, priv->regs + TSI721_OBDMAC_INTE(ch));


	iowrite32(0, priv->regs + TSI721_SMSG_INTE);


	for (ch = 0; ch < TSI721_DMA_MAXCH; ch++)
		iowrite32(0,
			priv->regs + TSI721_DMAC_BASE(ch) + TSI721_DMAC_INTE);


	iowrite32(0, priv->regs + TSI721_BDMA_INTE);


	for (ch = 0; ch < TSI721_SRIO_MAXCH; ch++)
		iowrite32(0, priv->regs + TSI721_SR_CHINTE(ch));


	iowrite32(0, priv->regs + TSI721_SR2PC_GEN_INTE);


	iowrite32(0, priv->regs + TSI721_PC2SR_INTE);


	iowrite32(0, priv->regs + TSI721_I2C_INT_ENABLE);


	iowrite32(0, priv->regs + TSI721_RIO_EM_INT_ENABLE);
	iowrite32(0, priv->regs + TSI721_RIO_EM_DEV_INT_EN);
}
