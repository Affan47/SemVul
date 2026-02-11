wm831x_status_src_store(struct device *dev,
				       struct device_attribute *attr,
				       const char *buf, size_t size)
{
	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	struct wm831x_status *led = to_wm831x_status(led_cdev);
	char name[20];
	int i;
	size_t len;

	name[sizeof(name) - 1] = '\0';
	strncpy(name, buf, sizeof(name) - 1);
	len = strlen(name);

	if (len && name[len - 1] == '\n')
		name[len - 1] = '\0';

	for (i = 0; i < ARRAY_SIZE(led_src_texts); i++) {
		if (!strcmp(name, led_src_texts[i])) {
			mutex_lock(&led->mutex);

			led->src = i;
			schedule_work(&led->work);

			mutex_unlock(&led->mutex);
		}
	}

	return size;
}
