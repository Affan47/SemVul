ir_open(void *data)
{
	int retval = 0;
	struct sasem_context *context;


	mutex_lock(&disconnect_lock);

	context = data;

	mutex_lock(&context->ctx_lock);

	if (context->ir_isopen) {
		dev_err(&context->dev->dev, "%s: IR port is already open\n",
			__func__);
		retval = -EBUSY;
		goto exit;
	}

	usb_fill_int_urb(context->rx_urb, context->dev,
		usb_rcvintpipe(context->dev,
				context->rx_endpoint->bEndpointAddress),
		context->usb_rx_buf, sizeof(context->usb_rx_buf),
		usb_rx_callback, context, context->rx_endpoint->bInterval);

	retval = usb_submit_urb(context->rx_urb, GFP_KERNEL);

	if (retval)
		dev_err(&context->dev->dev,
			"usb_submit_urb failed for ir_open (%d)\n", retval);
	else {
		context->ir_isopen = 1;
		dev_info(&context->dev->dev, "IR port opened\n");
	}

exit:
	mutex_unlock(&context->ctx_lock);

	mutex_unlock(&disconnect_lock);
	return retval;
}
