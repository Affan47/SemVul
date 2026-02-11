hda_widget_sysfs_init(struct hdac_device *codec)
{
	int err;

	if (codec->widgets)
		return 0;

	err = widget_tree_create(codec);
	if (err < 0) {
		widget_tree_free(codec);
		return err;
	}

	return 0;
}
