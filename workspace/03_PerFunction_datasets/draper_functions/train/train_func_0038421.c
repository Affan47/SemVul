softingcs_probe_config(struct pcmcia_device *pcmcia, void *priv_data)
{
	struct softing_platform_data *pdat = priv_data;
	struct resource *pres;
	int memspeed = 0;

	WARN_ON(!pdat);
	pres = pcmcia->resource[PCMCIA_IOMEM_0];
	if (resource_size(pres) < 0x1000)
		return -ERANGE;

	pres->flags |= WIN_MEMORY_TYPE_CM | WIN_ENABLE;
	if (pdat->generation < 2) {
		pres->flags |= WIN_USE_WAIT | WIN_DATA_WIDTH_8;
		memspeed = 3;
	} else {
		pres->flags |= WIN_DATA_WIDTH_16;
	}
	return pcmcia_request_window(pcmcia, pres, memspeed);
}
