lock_3_inodes(struct inode *inode1, struct inode *inode2,
			  struct inode *inode3)
{
	mutex_lock_nested(&ubifs_inode(inode1)->ui_mutex, WB_MUTEX_1);
	if (inode2 != inode1)
		mutex_lock_nested(&ubifs_inode(inode2)->ui_mutex, WB_MUTEX_2);
	if (inode3)
		mutex_lock_nested(&ubifs_inode(inode3)->ui_mutex, WB_MUTEX_3);
}
