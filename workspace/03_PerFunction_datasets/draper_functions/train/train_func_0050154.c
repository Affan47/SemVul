redrat3_handle_async(struct urb *urb)
{
	struct redrat3_dev *rr3;
	int ret;

	if (!urb)
		return;

	rr3 = urb->context;
	if (!rr3) {
		pr_err("%s called with invalid context!\n", __func__);
		usb_unlink_urb(urb);
		return;
	}

	switch (urb->status) {
	case 0:
		ret = redrat3_get_ir_data(rr3, urb->actual_length);
		if (!ret) {

			redrat3_issue_async(rr3);
		}
		break;

	case -ECONNRESET:
	case -ENOENT:
	case -ESHUTDOWN:
		usb_unlink_urb(urb);
		return;

	case -EPIPE:
	default:
		dev_warn(rr3->dev, "Error: urb status = %d\n", urb->status);
		rr3->bytes_read = 0;
		break;
	}
}
