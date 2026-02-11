rtl2832_sdr_enum_fmt_sdr_cap(struct file *file, void *priv,
		struct v4l2_fmtdesc *f)
{
	struct rtl2832_sdr_dev *dev = video_drvdata(file);
	struct platform_device *pdev = dev->pdev;

	dev_dbg(&pdev->dev, "\n");

	if (f->index >= dev->num_formats)
		return -EINVAL;

	strlcpy(f->description, formats[f->index].name, sizeof(f->description));
	f->pixelformat = formats[f->index].pixelformat;

	return 0;
}
