print_info(struct chip_info *info)
{
	if (verbose) {
		printf("Found %s %s Controller at 0x%x, DevID=0x%02x, Rev. %d\n",
		       info->manufacturer, info->name, info->cfg_base,
		       info->chip_id, info->revision);
		printf("    SIR Base 0x%x, FIR Base 0x%x\n",
		       info->sir_base, info->fir_base);
		printf("    IRQ = %d, DMA = %d\n", info->irq, info->dma);
		printf("    Enabled: %s, Suspended: %s\n",
		       info->enabled ? "yes" : "no",
		       info->suspended ? "yes" : "no");
		printf("    UART compatible: %s\n",
		       info->uart_comp ? "yes" : "no");
		printf("    Half duplex delay = %d us\n", info->delay);
	} else {
		printf("%s,%s,%d.%d,0x%x,0x%x,0x%x,%d,%d,%d,%d,%d\n",
		       info->manufacturer, info->name,
		       info->chip_id, info->revision, info->cfg_base,
		       info->sir_base, info->fir_base, info->irq, info->dma,
		       info->enabled, info->suspended, info->uart_comp);
	}
}
