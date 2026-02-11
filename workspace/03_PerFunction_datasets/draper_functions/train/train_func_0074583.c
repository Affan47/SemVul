mic_open(struct inode *inode, struct file *f)
{
	struct mic_vdev *mvdev;
	struct mic_device *mdev = container_of(f->private_data,
		struct mic_device, miscdev);

	mvdev = kzalloc(sizeof(*mvdev), GFP_KERNEL);
	if (!mvdev)
		return -ENOMEM;

	init_waitqueue_head(&mvdev->waitq);
	INIT_LIST_HEAD(&mvdev->list);
	mvdev->mdev = mdev;
	mvdev->virtio_id = -1;

	f->private_data = mvdev;
	return 0;
}
