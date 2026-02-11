capi_open(struct inode *inode, struct file *file)
{
	struct capidev *cdev;

	cdev = kzalloc(sizeof(*cdev), GFP_KERNEL);
	if (!cdev)
		return -ENOMEM;

	mutex_init(&cdev->lock);
	skb_queue_head_init(&cdev->recvqueue);
	init_waitqueue_head(&cdev->recvwait);
	INIT_LIST_HEAD(&cdev->nccis);
	file->private_data = cdev;

	mutex_lock(&capidev_list_lock);
	list_add_tail(&cdev->list, &capidev_list);
	mutex_unlock(&capidev_list_lock);

	return nonseekable_open(inode, file);
}
