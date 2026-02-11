fcoe_fcf_get_selected(struct fcoe_fcf_device *fcf_dev)
{
	struct fcoe_ctlr_device *ctlr_dev = fcoe_fcf_dev_to_ctlr_dev(fcf_dev);
	struct fcoe_ctlr *fip = fcoe_ctlr_device_priv(ctlr_dev);
	struct fcoe_fcf *fcf;

	mutex_lock(&fip->ctlr_mutex);
	mutex_lock(&ctlr_dev->lock);

	fcf = fcoe_fcf_device_priv(fcf_dev);
	if (fcf)
		fcf_dev->selected = (fcf == fip->sel_fcf) ? 1 : 0;
	else
		fcf_dev->selected = 0;

	mutex_unlock(&ctlr_dev->lock);
	mutex_unlock(&fip->ctlr_mutex);
}
