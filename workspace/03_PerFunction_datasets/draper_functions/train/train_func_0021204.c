is_connected(struct input_conn *iconn)
{
	struct input_device *idev = iconn->idev;
	struct fake_input *fake = iconn->fake;
	struct hidp_conninfo ci;
	int ctl;


	if (fake)
		return fake->flags & FI_FLAG_CONNECTED;


	ctl = socket(AF_BLUETOOTH, SOCK_RAW, BTPROTO_HIDP);
	if (ctl < 0)
		return 0;

	memset(&ci, 0, sizeof(ci));
	bacpy(&ci.bdaddr, &idev->dst);
	if (ioctl(ctl, HIDPGETCONNINFO, &ci) < 0) {
		close(ctl);
		return 0;
	}

	close(ctl);

	if (ci.state != BT_CONNECTED)
		return 0;
	else
		return 1;
}
