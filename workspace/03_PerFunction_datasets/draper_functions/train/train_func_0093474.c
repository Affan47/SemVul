ext4_mb_new_preallocation(struct ext4_allocation_context *ac)
{
	int err;

	if (ac->ac_flags & EXT4_MB_HINT_GROUP_ALLOC)
		err = ext4_mb_new_group_pa(ac);
	else
		err = ext4_mb_new_inode_pa(ac);
	return err;
}
