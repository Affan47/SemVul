usb_tx_callback(struct urb *urb)
{
	struct imon_context *ictx;

	if (!urb)
		return;
	ictx = (struct imon_context *)urb->context;
	if (!ictx)
		return;

	ictx->tx.status = urb->status;


	ictx->tx.busy = false;
	smp_rmb();
	complete(&ictx->tx.finished);
}
