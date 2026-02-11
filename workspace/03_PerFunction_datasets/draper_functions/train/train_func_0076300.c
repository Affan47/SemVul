channel_id_show(struct device *dev,
			       struct device_attribute *attr,
			       char *buf) {
	struct visor_device *vdev = to_visor_device(dev);
	int len = 0;

	if (vdev->visorchannel) {
		visorchannel_id(vdev->visorchannel, buf);
		len = strlen(buf);
		buf[len++] = '\n';
	}
	return len;
}
