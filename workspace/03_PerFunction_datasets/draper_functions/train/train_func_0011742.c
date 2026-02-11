virtio_gpu_probe(struct virtio_device *vdev)
{
#ifdef CONFIG_VGA_CONSOLE
	if (vgacon_text_force() && virtio_gpu_modeset == -1)
		return -EINVAL;
#endif

	if (virtio_gpu_modeset == 0)
		return -EINVAL;

	return drm_virtio_init(&driver, vdev);
}
