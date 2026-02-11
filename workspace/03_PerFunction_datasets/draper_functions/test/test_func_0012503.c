vp_finalize_features(struct virtio_device *vdev)
{
	struct virtio_pci_device *vp_dev = to_vp_device(vdev);


	vring_transport_features(vdev);

	if (!__virtio_test_bit(vdev, VIRTIO_F_VERSION_1)) {
		dev_err(&vdev->dev, "virtio: device uses modern interface "
			"but does not have VIRTIO_F_VERSION_1\n");
		return -EINVAL;
	}

	vp_iowrite32(0, &vp_dev->common->guest_feature_select);
	vp_iowrite32((u32)vdev->features, &vp_dev->common->guest_feature);
	vp_iowrite32(1, &vp_dev->common->guest_feature_select);
	vp_iowrite32(vdev->features >> 32, &vp_dev->common->guest_feature);

	return 0;
}
