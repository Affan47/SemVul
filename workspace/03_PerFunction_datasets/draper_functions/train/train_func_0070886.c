cobalt_notify(struct v4l2_subdev *sd,
			  unsigned int notification, void *arg)
{
	struct cobalt *cobalt = to_cobalt(sd->v4l2_dev);
	unsigned sd_nr = cobalt_get_sd_nr(sd);
	struct cobalt_stream *s = &cobalt->streams[sd_nr];
	bool hotplug = arg ? *((int *)arg) : false;

	if (s->is_output)
		return;

	switch (notification) {
	case ADV76XX_HOTPLUG:
		cobalt_s_bit_sysctrl(cobalt,
			COBALT_SYS_CTRL_HPD_TO_CONNECTOR_BIT(sd_nr), hotplug);
		cobalt_dbg(1, "Set hotplug for adv %d to %d\n", sd_nr, hotplug);
		break;
	case V4L2_DEVICE_NOTIFY_EVENT:
		cobalt_dbg(1, "Format changed for adv %d\n", sd_nr);
		v4l2_event_queue(&s->vdev, arg);
		break;
	default:
		break;
	}
}
