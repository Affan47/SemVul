configfs_release(struct inode * inode, struct file * filp)
{
	struct config_item * item = to_item(filp->f_path.dentry->d_parent);
	struct configfs_attribute * attr = to_attr(filp->f_path.dentry);
	struct module * owner = attr->ca_owner;
	struct configfs_buffer * buffer = filp->private_data;

	if (item)
		config_item_put(item);

	module_put(owner);

	if (buffer) {
		if (buffer->page)
			free_page((unsigned long)buffer->page);
		mutex_destroy(&buffer->mutex);
		kfree(buffer);
	}
	return 0;
}
