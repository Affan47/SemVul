get_interval(struct urb *urb, __u8 interval)
{
	u16 time = 1;
	int i;

	if (urb->dev->speed == USB_SPEED_HIGH) {
		if (interval > IITV)
			time = IITV;
		else
			time = interval ? interval - 1 : 0;
	} else {
		if (interval > 128) {
			time = IITV;
		} else {

			for (i = 0; i < 7; i++) {
				if ((1 << i) < interval &&
				    (1 << (i + 1) > interval))
					time = 1 << i;
			}
		}
	}

	return time;
}
