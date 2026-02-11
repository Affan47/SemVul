enable_hwirq(struct inf_hw *hw)
{
	u16 w;
	u32 val;

	switch (hw->ci->typ) {
	case INF_DIVA201:
	case INF_DIVA202:
		writel(PITA_INT0_ENABLE, hw->cfg.p);
		break;
	case INF_SPEEDWIN:
	case INF_SAPHIR3:
		outb(TIGER_IRQ_BIT, (u32)hw->cfg.start + TIGER_AUX_IRQMASK);
		break;
	case INF_QS1000:
		outb(QS1000_IRQ_ON, (u32)hw->cfg.start + ELSA_IRQ_ADDR);
		break;
	case INF_QS3000:
		outb(QS3000_IRQ_ON, (u32)hw->cfg.start + ELSA_IRQ_ADDR);
		break;
	case INF_NICCY:
		val = inl((u32)hw->cfg.start + NICCY_IRQ_CTRL_REG);
		val |= NICCY_IRQ_ENABLE;
		outl(val, (u32)hw->cfg.start + NICCY_IRQ_CTRL_REG);
		break;
	case INF_SCT_1:
		w = inw((u32)hw->cfg.start + SCT_PLX_IRQ_ADDR);
		w |= SCT_PLX_IRQ_ENABLE;
		outw(w, (u32)hw->cfg.start + SCT_PLX_IRQ_ADDR);
		break;
	case INF_GAZEL_R685:
		outb(GAZEL_ISAC_EN + GAZEL_HSCX_EN + GAZEL_PCI_EN,
		     (u32)hw->cfg.start + GAZEL_INCSR);
		break;
	case INF_GAZEL_R753:
		outb(GAZEL_IPAC_EN + GAZEL_PCI_EN,
		     (u32)hw->cfg.start + GAZEL_INCSR);
		break;
	default:
		break;
	}
}
