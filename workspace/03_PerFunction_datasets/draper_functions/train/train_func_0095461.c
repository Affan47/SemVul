sil24_config_port(struct ata_port *ap)
{
	void __iomem *port = sil24_port_base(ap);


	if (ap->flags & SIL24_FLAG_PCIX_IRQ_WOC)
		writel(PORT_CS_IRQ_WOC, port + PORT_CTRL_STAT);
	else
		writel(PORT_CS_IRQ_WOC, port + PORT_CTRL_CLR);


	writew(0x8000, port + PORT_DECODE_ERR_THRESH);
	writew(0x8000, port + PORT_CRC_ERR_THRESH);
	writew(0x8000, port + PORT_HSHK_ERR_THRESH);
	writew(0x0000, port + PORT_DECODE_ERR_CNT);
	writew(0x0000, port + PORT_CRC_ERR_CNT);
	writew(0x0000, port + PORT_HSHK_ERR_CNT);


	writel(PORT_CS_32BIT_ACTV, port + PORT_CTRL_CLR);


	writel(PORT_CS_PMP_EN | PORT_CS_PMP_RESUME, port + PORT_CTRL_CLR);
}
