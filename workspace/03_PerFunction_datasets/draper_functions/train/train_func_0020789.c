hdmi_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct hdmi_device *hdev = sd_to_hdmi_dev(sd);
	struct device *dev = hdev->dev;

	dev_dbg(dev, "%s(%d)\n", __func__, enable);
	if (enable)
		return hdmi_streamon(hdev);
	return hdmi_streamoff(hdev);
}
