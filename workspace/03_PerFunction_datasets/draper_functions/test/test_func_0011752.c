mic_virtio_init_post(struct mic_vdev *mvdev)
{
	struct mic_vqconfig *vqconfig = mic_vq_config(mvdev->dd);
	int i;

	for (i = 0; i < mvdev->dd->num_vq; i++) {
		if (!le64_to_cpu(vqconfig[i].used_address)) {
			dev_warn(mic_dev(mvdev), "used_address zero??\n");
			continue;
		}
		mvdev->mvr[i].vrh.vring.used =
			(void __force *)mvdev->mdev->aper.va +
			le64_to_cpu(vqconfig[i].used_address);
	}

	mvdev->dc->used_address_updated = 0;

	dev_dbg(mic_dev(mvdev), "%s: device type %d LINKUP\n",
		__func__, mvdev->virtio_id);
}
