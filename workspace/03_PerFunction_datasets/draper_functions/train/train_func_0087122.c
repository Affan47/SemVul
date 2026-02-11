r_heartbeat_file_open(struct inode *inode, struct file *file)
{
	struct ibmasmfs_heartbeat_data *rhbeat;

	if (!inode->i_private)
		return -ENODEV;

	rhbeat = kmalloc(sizeof(struct ibmasmfs_heartbeat_data), GFP_KERNEL);
	if (!rhbeat)
		return -ENOMEM;

	rhbeat->sp = inode->i_private;
	rhbeat->active = 0;
	ibmasm_init_reverse_heartbeat(rhbeat->sp, &rhbeat->heartbeat);
	file->private_data = rhbeat;
	return 0;
}
