us122l_start(struct us122l *us122l,
			 unsigned rate, unsigned period_frames)
{
	struct list_head *p;
	int err;
	unsigned use_packsize = 0;
	bool success = false;

	if (us122l->dev->speed == USB_SPEED_HIGH) {


		switch (rate) {
		case 44100:
			use_packsize = 36;
			break;
		case 48000:
			use_packsize = 42;
			break;
		case 88200:
			use_packsize = 72;
			break;
		}
	}
	if (!usb_stream_new(&us122l->sk, us122l->dev, 1, 2,
			    rate, use_packsize, period_frames, 6))
		goto out;

	err = us122l_set_sample_rate(us122l->dev, rate);
	if (err < 0) {
		us122l_stop(us122l);
		snd_printk(KERN_ERR "us122l_set_sample_rate error \n");
		goto out;
	}
	err = usb_stream_start(&us122l->sk);
	if (err < 0) {
		us122l_stop(us122l);
		snd_printk(KERN_ERR "us122l_start error %i \n", err);
		goto out;
	}
	list_for_each(p, &us122l->midi_list)
		snd_usbmidi_input_start(p);
	success = true;
out:
	return success;
}
