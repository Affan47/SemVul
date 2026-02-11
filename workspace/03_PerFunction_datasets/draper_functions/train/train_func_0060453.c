__wa_destroy(struct wahc *wa)
{
	if (wa->dti_urb) {
		usb_kill_urb(wa->dti_urb);
		usb_put_urb(wa->dti_urb);
	}
	kfree(wa->dti_buf);
	wa_nep_destroy(wa);
	wa_rpipes_destroy(wa);
}
