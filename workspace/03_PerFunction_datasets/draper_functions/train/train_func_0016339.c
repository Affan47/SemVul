jme_set_rx_pcc(struct jme_adapter *jme, int p)
{
	switch (p) {
	case PCC_OFF:
		jwrite32(jme, JME_PCCRX0,
			((PCC_OFF_TO << PCCRXTO_SHIFT) & PCCRXTO_MASK) |
			((PCC_OFF_CNT << PCCRX_SHIFT) & PCCRX_MASK));
		break;
	case PCC_P1:
		jwrite32(jme, JME_PCCRX0,
			((PCC_P1_TO << PCCRXTO_SHIFT) & PCCRXTO_MASK) |
			((PCC_P1_CNT << PCCRX_SHIFT) & PCCRX_MASK));
		break;
	case PCC_P2:
		jwrite32(jme, JME_PCCRX0,
			((PCC_P2_TO << PCCRXTO_SHIFT) & PCCRXTO_MASK) |
			((PCC_P2_CNT << PCCRX_SHIFT) & PCCRX_MASK));
		break;
	case PCC_P3:
		jwrite32(jme, JME_PCCRX0,
			((PCC_P3_TO << PCCRXTO_SHIFT) & PCCRXTO_MASK) |
			((PCC_P3_CNT << PCCRX_SHIFT) & PCCRX_MASK));
		break;
	default:
		break;
	}
	wmb();

	if (!(test_bit(JME_FLAG_POLL, &jme->flags)))
		netif_info(jme, rx_status, jme->dev, "Switched to PCC_P%d\n", p);
}
