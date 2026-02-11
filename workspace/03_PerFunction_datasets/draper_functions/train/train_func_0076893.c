fcoe_fcf_set_dev_loss_tmo(struct fcoe_fcf_device *fcf,
				     unsigned long val)
{
	if ((fcf->state == FCOE_FCF_STATE_UNKNOWN) ||
	    (fcf->state == FCOE_FCF_STATE_DISCONNECTED) ||
	    (fcf->state == FCOE_FCF_STATE_DELETED))
		return -EBUSY;


	if (val > UINT_MAX)
		return -EINVAL;

	fcoe_fcf_dev_loss_tmo(fcf) = val;
	return 0;
}
