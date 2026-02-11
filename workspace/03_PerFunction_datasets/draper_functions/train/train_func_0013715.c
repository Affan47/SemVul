mv_reset_channel(struct mv_host_priv *hpriv, void __iomem *mmio,
			     unsigned int port_no)
{
	void __iomem *port_mmio = mv_port_base(mmio, port_no);


	mv_stop_edma_engine(port_mmio);
	writelfl(EDMA_RESET, port_mmio + EDMA_CMD);

	if (!IS_GEN_I(hpriv)) {

		mv_setup_ifcfg(port_mmio, 1);
	}


	writelfl(EDMA_RESET, port_mmio + EDMA_CMD);
	udelay(25);
	writelfl(0, port_mmio + EDMA_CMD);

	hpriv->ops->phy_errata(hpriv, mmio, port_no);

	if (IS_GEN_I(hpriv))
		mdelay(1);
}
