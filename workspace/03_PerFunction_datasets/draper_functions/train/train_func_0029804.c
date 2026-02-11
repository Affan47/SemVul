adv7842_ioctl(struct v4l2_subdev *sd, unsigned int cmd, void *arg)
{
	switch (cmd) {
	case ADV7842_CMD_RAM_TEST:
		return adv7842_command_ram_test(sd);
	}
	return -ENOTTY;
}
