ch7xxx_detect(struct intel_dvo_device *dvo)
{
	uint8_t cdet, orig_pm, pm;

	ch7xxx_readb(dvo, CH7xxx_PM, &orig_pm);

	pm = orig_pm;
	pm &= ~CH7xxx_PM_FPD;
	pm |= CH7xxx_PM_DVIL | CH7xxx_PM_DVIP;

	ch7xxx_writeb(dvo, CH7xxx_PM, pm);

	ch7xxx_readb(dvo, CH7xxx_CONNECTION_DETECT, &cdet);

	ch7xxx_writeb(dvo, CH7xxx_PM, orig_pm);

	if (cdet & CH7xxx_CDET_DVI)
		return connector_status_connected;
	return connector_status_disconnected;
}
