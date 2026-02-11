ilo_write(struct file *fp, const char __user *buf,
			 size_t len, loff_t *off)
{
	int err, pkt_id, pkt_len;
	struct ccb_data *data = fp->private_data;
	struct ccb *driver_ccb = &data->driver_ccb;
	struct ilo_hwinfo *hw = data->ilo_hw;
	void *pkt;

	if (is_channel_reset(driver_ccb))
		return -ENODEV;


	if (!ilo_pkt_dequeue(hw, driver_ccb, SENDQ, &pkt_id, &pkt_len, &pkt))
		return -EBUSY;


	if (pkt_len < len)
		len = pkt_len;


	err = copy_from_user(pkt, buf, len);
	if (err)
		len = 0;


	ilo_pkt_enqueue(hw, driver_ccb, SENDQ, pkt_id, len);
	doorbell_set(driver_ccb);

	return err ? -EFAULT : len;
}
