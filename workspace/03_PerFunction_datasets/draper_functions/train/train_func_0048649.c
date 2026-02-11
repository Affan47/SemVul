xsd_kva_open(struct inode *inode, struct file *file)
{
	file->private_data = (void *)kasprintf(GFP_KERNEL, "0x%p",
					       xen_store_interface);
	if (!file->private_data)
		return -ENOMEM;
	return 0;
}
