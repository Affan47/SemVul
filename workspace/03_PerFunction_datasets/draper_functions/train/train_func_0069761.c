mos7840_control_callback(struct urb *urb)
{
	unsigned char *data;
	struct moschip_port *mos7840_port;
	struct device *dev = &urb->dev->dev;
	__u8 regval = 0x0;
	int status = urb->status;

	mos7840_port = urb->context;

	switch (status) {
	case 0:

		break;
	case -ECONNRESET:
	case -ENOENT:
	case -ESHUTDOWN:

		dev_dbg(dev, "%s - urb shutting down with status: %d\n", __func__, status);
		goto out;
	default:
		dev_dbg(dev, "%s - nonzero urb status received: %d\n", __func__, status);
		goto out;
	}

	dev_dbg(dev, "%s urb buffer size is %d\n", __func__, urb->actual_length);
	dev_dbg(dev, "%s mos7840_port->MsrLsr is %d port %d\n", __func__,
		mos7840_port->MsrLsr, mos7840_port->port_num);
	data = urb->transfer_buffer;
	regval = (__u8) data[0];
	dev_dbg(dev, "%s data is %x\n", __func__, regval);
	if (mos7840_port->MsrLsr == 0)
		mos7840_handle_new_msr(mos7840_port, regval);
	else if (mos7840_port->MsrLsr == 1)
		mos7840_handle_new_lsr(mos7840_port, regval);
out:
	clear_bit_unlock(MOS7840_FLAG_CTRL_BUSY, &mos7840_port->flags);
}
