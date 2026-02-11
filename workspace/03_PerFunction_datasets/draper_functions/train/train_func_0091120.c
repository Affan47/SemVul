mic_find_vqs(struct virtio_device *vdev, unsigned nvqs,
			struct virtqueue *vqs[],
			vq_callback_t *callbacks[],
			const char *names[])
{
	struct mic_vdev *mvdev = to_micvdev(vdev);
	struct mic_device_ctrl __iomem *dc = mvdev->dc;
	int i, err, retry;


	if (nvqs > ioread8(&mvdev->desc->num_vq))
		return -ENOENT;

	for (i = 0; i < nvqs; ++i) {
		dev_dbg(mic_dev(mvdev), "%s: %d: %s\n",
			__func__, i, names[i]);
		vqs[i] = mic_find_vq(vdev, i, callbacks[i], names[i]);
		if (IS_ERR(vqs[i])) {
			err = PTR_ERR(vqs[i]);
			goto error;
		}
	}

	iowrite8(1, &dc->used_address_updated);


	mic_send_intr(mvdev->mdev, mvdev->c2h_vdev_db);
	for (retry = 100; retry--;) {
		if (!ioread8(&dc->used_address_updated))
			break;
		msleep(100);
	};

	dev_dbg(mic_dev(mvdev), "%s: retry: %d\n", __func__, retry);
	if (!retry) {
		err = -ENODEV;
		goto error;
	}

	return 0;
error:
	mic_del_vqs(vdev);
	return err;
}
