pch_can_int_clr(struct pch_can_priv *priv, u32 mask)
{

	if ((mask >= PCH_RX_OBJ_START) && (mask <= PCH_RX_OBJ_END)) {

		iowrite32(PCH_CMASK_RDWR | PCH_CMASK_CTRL | PCH_CMASK_ARB,
			  &priv->regs->ifregs[0].cmask);


		pch_can_bit_clear(&priv->regs->ifregs[0].id2, PCH_ID2_DIR);


		pch_can_bit_clear(&priv->regs->ifregs[0].mcont,
				  PCH_IF_MCONT_NEWDAT | PCH_IF_MCONT_INTPND);

		pch_can_rw_msg_obj(&priv->regs->ifregs[0].creq, mask);
	} else if ((mask >= PCH_TX_OBJ_START) && (mask <= PCH_TX_OBJ_END)) {


		iowrite32(PCH_CMASK_RDWR | PCH_CMASK_CTRL | PCH_CMASK_ARB,
			  &priv->regs->ifregs[1].cmask);


		pch_can_bit_set(&priv->regs->ifregs[1].id2,
			       PCH_ID2_DIR | (0x7ff << 2));
		iowrite32(0x0, &priv->regs->ifregs[1].id1);


		pch_can_bit_clear(&priv->regs->ifregs[1].mcont,
				  PCH_IF_MCONT_NEWDAT | PCH_IF_MCONT_INTPND |
				  PCH_IF_MCONT_TXRQXT);
		pch_can_rw_msg_obj(&priv->regs->ifregs[1].creq, mask);
	}
}
