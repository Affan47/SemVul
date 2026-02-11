tt3650_ci_set_video_port(struct dvb_ca_en50221 *ca, int slot, int enable)
{
	u8 buf[1];
	int ret;

	ci_dbg("%d %d", slot, enable);

	if (slot)
		return -EINVAL;

	buf[0] = enable;

	ret = tt3650_ci_msg_locked(ca, TT3650_CMD_CI_SET_VIDEO_PORT, buf, 1, 1);
	if (ret < 0)
		return ret;

	if (enable != buf[0]) {
		err("CI not %sabled.", enable ? "en" : "dis");
		return -EIO;
	}

	return 0;
}
