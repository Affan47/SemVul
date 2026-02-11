vidioc_g_chip_info(struct file *file, void *priv,
			      struct v4l2_dbg_chip_info *chip)
{
	struct em28xx *dev = video_drvdata(file);

	if (chip->match.addr > 1)
		return -EINVAL;
	if (chip->match.addr == 1)
		strlcpy(chip->name, "ac97", sizeof(chip->name));
	else
		strlcpy(chip->name,
			dev->v4l2->v4l2_dev.name, sizeof(chip->name));
	return 0;
}
