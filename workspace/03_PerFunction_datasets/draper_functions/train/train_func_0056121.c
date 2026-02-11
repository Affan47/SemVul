cx18_gpio_register(struct cx18 *cx, u32 hw)
{
	struct v4l2_subdev *sd;
	const struct v4l2_subdev_ops *ops;
	char *str;

	switch (hw) {
	case CX18_HW_GPIO_MUX:
		sd = &cx->sd_gpiomux;
		ops = &gpiomux_ops;
		str = "gpio-mux";
		break;
	case CX18_HW_GPIO_RESET_CTRL:
		sd = &cx->sd_resetctrl;
		ops = &resetctrl_ops;
		str = "gpio-reset-ctrl";
		break;
	default:
		return -EINVAL;
	}

	v4l2_subdev_init(sd, ops);
	v4l2_set_subdevdata(sd, cx);
	snprintf(sd->name, sizeof(sd->name), "%s %s", cx->v4l2_dev.name, str);
	sd->grp_id = hw;
	return v4l2_device_register_subdev(&cx->v4l2_dev, sd);
}
