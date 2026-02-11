iguanair_send(struct iguanair *ir, unsigned size)
{
	int rc;

	reinit_completion(&ir->completion);

	ir->urb_out->transfer_buffer_length = size;
	rc = usb_submit_urb(ir->urb_out, GFP_KERNEL);
	if (rc)
		return rc;

	if (wait_for_completion_timeout(&ir->completion, TIMEOUT) == 0)
		return -ETIMEDOUT;

	return rc;
}
