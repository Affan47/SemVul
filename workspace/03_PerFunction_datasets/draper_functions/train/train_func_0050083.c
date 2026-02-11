ecryptfs_miscdev_open(struct inode *inode, struct file *file)
{
	struct ecryptfs_daemon *daemon = NULL;
	int rc;

	mutex_lock(&ecryptfs_daemon_hash_mux);
	rc = ecryptfs_find_daemon_by_euid(&daemon);
	if (!rc) {
		rc = -EINVAL;
		goto out_unlock_daemon_list;
	}
	rc = ecryptfs_spawn_daemon(&daemon, file);
	if (rc) {
		printk(KERN_ERR "%s: Error attempting to spawn daemon; "
		       "rc = [%d]\n", __func__, rc);
		goto out_unlock_daemon_list;
	}
	mutex_lock(&daemon->mux);
	if (daemon->flags & ECRYPTFS_DAEMON_MISCDEV_OPEN) {
		rc = -EBUSY;
		goto out_unlock_daemon;
	}
	daemon->flags |= ECRYPTFS_DAEMON_MISCDEV_OPEN;
	file->private_data = daemon;
	atomic_inc(&ecryptfs_num_miscdev_opens);
out_unlock_daemon:
	mutex_unlock(&daemon->mux);
out_unlock_daemon_list:
	mutex_unlock(&ecryptfs_daemon_hash_mux);
	return rc;
}
