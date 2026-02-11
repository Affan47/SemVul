urb_destroy(struct kref *kref)
{
	struct urb *urb = to_urb(kref);

	if (urb->transfer_flags & URB_FREE_BUFFER)
		kfree(urb->transfer_buffer);

	kfree(urb);
}
