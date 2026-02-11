vsxxxaa_handle_ABS_packet(struct vsxxxaa *mouse)
{
	struct input_dev *dev = mouse->dev;
	unsigned char *buf = mouse->buf;
	int left, middle, right, touch;
	int x, y;


	x = ((buf[2] & 0x3f) << 6) | (buf[1] & 0x3f);
	y = ((buf[4] & 0x3f) << 6) | (buf[3] & 0x3f);
	y = 1023 - y;


	left	= buf[0] & 0x02;
	middle	= buf[0] & 0x04;
	right	= buf[0] & 0x08;
	touch	= buf[0] & 0x10;

	vsxxxaa_drop_bytes(mouse, 5);

	DBG(KERN_INFO "%s on %s: x=%d, y=%d, buttons=%s%s%s%s\n",
	    mouse->name, mouse->phys, x, y,
	    left ? "L" : "l", middle ? "M" : "m",
	    right ? "R" : "r", touch ? "T" : "t");


	input_report_key(dev, BTN_LEFT, left);
	input_report_key(dev, BTN_MIDDLE, middle);
	input_report_key(dev, BTN_RIGHT, right);
	input_report_key(dev, BTN_TOUCH, touch);
	input_report_abs(dev, ABS_X, x);
	input_report_abs(dev, ABS_Y, y);
	input_sync(dev);
}
