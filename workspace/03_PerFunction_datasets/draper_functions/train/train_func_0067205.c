snd_hdac_device_register(struct hdac_device *codec)
{
	int err;

	err = device_add(&codec->dev);
	if (err < 0)
		return err;
	err = hda_widget_sysfs_init(codec);
	if (err < 0) {
		device_del(&codec->dev);
		return err;
	}

	return 0;
}
