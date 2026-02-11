mic_get(struct virtio_device *vdev, unsigned int offset,
		   void *buf, unsigned len)
{
	struct mic_device_desc __iomem *desc = to_micvdev(vdev)->desc;

	if (offset + len > ioread8(&desc->config_len))
		return;
	memcpy_fromio(buf, mic_vq_configspace(desc) + offset, len);
}
