ci_hdrc_gadget_init(struct ci_hdrc *ci)
{
	struct ci_role_driver *rdrv;
	int ret;

	if (!hw_read(ci, CAP_DCCPARAMS, DCCPARAMS_DC))
		return -ENXIO;

	rdrv = devm_kzalloc(ci->dev, sizeof(struct ci_role_driver), GFP_KERNEL);
	if (!rdrv)
		return -ENOMEM;

	rdrv->start	= udc_id_switch_for_device;
	rdrv->stop	= udc_id_switch_for_host;
	rdrv->irq	= udc_irq;
	rdrv->name	= "gadget";

	ret = udc_start(ci);
	if (!ret)
		ci->roles[CI_ROLE_GADGET] = rdrv;

	return ret;
}
