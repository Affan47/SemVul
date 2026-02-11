bt819_s_std(struct v4l2_subdev *sd, v4l2_std_id std)
{
	struct bt819 *decoder = to_bt819(sd);
	struct timing *timing = NULL;

	v4l2_dbg(1, debug, sd, "set norm %llx\n", (unsigned long long)std);

	if (sd->v4l2_dev == NULL || sd->v4l2_dev->notify == NULL)
		v4l2_err(sd, "no notify found!\n");

	if (std & V4L2_STD_NTSC) {
		v4l2_subdev_notify(sd, BT819_FIFO_RESET_LOW, NULL);
		bt819_setbit(decoder, 0x01, 0, 1);
		bt819_setbit(decoder, 0x01, 1, 0);
		bt819_setbit(decoder, 0x01, 5, 0);
		bt819_write(decoder, 0x18, 0x68);
		bt819_write(decoder, 0x19, 0x5d);

		timing = &timing_data[1];
	} else if (std & V4L2_STD_PAL) {
		v4l2_subdev_notify(sd, BT819_FIFO_RESET_LOW, NULL);
		bt819_setbit(decoder, 0x01, 0, 1);
		bt819_setbit(decoder, 0x01, 1, 1);
		bt819_setbit(decoder, 0x01, 5, 1);
		bt819_write(decoder, 0x18, 0x7f);
		bt819_write(decoder, 0x19, 0x72);

		timing = &timing_data[0];
	} else {
		v4l2_dbg(1, debug, sd, "unsupported norm %llx\n",
				(unsigned long long)std);
		return -EINVAL;
	}
	bt819_write(decoder, 0x03,
			(((timing->vdelay >> 8) & 0x03) << 6) |
			(((timing->vactive >> 8) & 0x03) << 4) |
			(((timing->hdelay >> 8) & 0x03) << 2) |
			((timing->hactive >> 8) & 0x03));
	bt819_write(decoder, 0x04, timing->vdelay & 0xff);
	bt819_write(decoder, 0x05, timing->vactive & 0xff);
	bt819_write(decoder, 0x06, timing->hdelay & 0xff);
	bt819_write(decoder, 0x07, timing->hactive & 0xff);
	bt819_write(decoder, 0x08, (timing->hscale >> 8) & 0xff);
	bt819_write(decoder, 0x09, timing->hscale & 0xff);
	decoder->norm = std;
	v4l2_subdev_notify(sd, BT819_FIFO_RESET_HIGH, NULL);
	return 0;
}
