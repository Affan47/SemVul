ttusbir_set_led(struct ttusbir *tt)
{
	int ret;

	smp_mb();

	if (tt->led_on != tt->is_led_on && tt->udev &&
				atomic_add_unless(&tt->led_complete, 1, 1)) {
		tt->bulk_buffer[4] = tt->is_led_on = tt->led_on;
		ret = usb_submit_urb(tt->bulk_urb, GFP_ATOMIC);
		if (ret) {
			dev_warn(tt->dev, "failed to submit bulk urb: %d\n",
									ret);
			atomic_dec(&tt->led_complete);
		}
	}
}
