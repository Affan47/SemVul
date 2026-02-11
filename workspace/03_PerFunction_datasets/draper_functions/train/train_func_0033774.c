get_registers(struct r8152 *tp, u16 value, u16 index, u16 size, void *data)
{
	int ret;
	void *tmp;

	tmp = kmalloc(size, GFP_KERNEL);
	if (!tmp)
		return -ENOMEM;

	ret = usb_control_msg(tp->udev, usb_rcvctrlpipe(tp->udev, 0),
			      RTL8152_REQ_GET_REGS, RTL8152_REQT_READ,
			      value, index, tmp, size, 500);

	memcpy(data, tmp, size);
	kfree(tmp);

	return ret;
}
