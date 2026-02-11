adv7183_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct adv7183 *decoder = to_adv7183(sd);

	if (enable)
		gpio_set_value(decoder->oe_pin, 0);
	else
		gpio_set_value(decoder->oe_pin, 1);
	udelay(1);
	return 0;
}
