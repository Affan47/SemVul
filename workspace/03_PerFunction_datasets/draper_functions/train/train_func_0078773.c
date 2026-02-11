ion_test_open(struct inode *inode, struct file *file)
{
	struct ion_test_data *data;
	struct miscdevice *miscdev = file->private_data;

	data = kzalloc(sizeof(struct ion_test_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->dev = miscdev->parent;

	file->private_data = data;

	return 0;
}
