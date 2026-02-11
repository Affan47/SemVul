gc_n64_process_packet(struct gc *gc)
{
	unsigned char data[GC_N64_LENGTH];
	struct input_dev *dev;
	int i, j, s;
	signed char x, y;

	gc_n64_read_packet(gc, data);

	for (i = 0; i < GC_MAX_DEVICES; i++) {

		if (gc->pads[i].type != GC_N64)
			continue;

		dev = gc->pads[i].dev;
		s = gc_status_bit[i];

		if (s & ~(data[8] | data[9])) {

			x = y = 0;

			for (j = 0; j < 8; j++) {
				if (data[23 - j] & s)
					x |= 1 << j;
				if (data[31 - j] & s)
					y |= 1 << j;
			}

			input_report_abs(dev, ABS_X,  x);
			input_report_abs(dev, ABS_Y, -y);

			input_report_abs(dev, ABS_HAT0X,
					 !(s & data[6]) - !(s & data[7]));
			input_report_abs(dev, ABS_HAT0Y,
					 !(s & data[4]) - !(s & data[5]));

			for (j = 0; j < 10; j++)
				input_report_key(dev, gc_n64_btn[j],
						 s & data[gc_n64_bytes[j]]);

			input_sync(dev);
		}
	}
}
