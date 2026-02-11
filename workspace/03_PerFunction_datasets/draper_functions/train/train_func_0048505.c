dbg_check_inode_size(struct ubifs_info *c, const struct inode *inode,
			 loff_t size)
{
	int err, n;
	union ubifs_key from_key, to_key, *key;
	struct ubifs_znode *znode;
	unsigned int block;

	if (!S_ISREG(inode->i_mode))
		return 0;
	if (!dbg_is_chk_gen(c))
		return 0;

	block = (size + UBIFS_BLOCK_SIZE - 1) >> UBIFS_BLOCK_SHIFT;
	data_key_init(c, &from_key, inode->i_ino, block);
	highest_data_key(c, &to_key, inode->i_ino);

	mutex_lock(&c->tnc_mutex);
	err = ubifs_lookup_level0(c, &from_key, &znode, &n);
	if (err < 0)
		goto out_unlock;

	if (err) {
		key = &from_key;
		goto out_dump;
	}

	err = tnc_next(c, &znode, &n);
	if (err == -ENOENT) {
		err = 0;
		goto out_unlock;
	}
	if (err < 0)
		goto out_unlock;

	ubifs_assert(err == 0);
	key = &znode->zbranch[n].key;
	if (!key_in_range(c, key, &from_key, &to_key))
		goto out_unlock;

out_dump:
	block = key_block(c, key);
	ubifs_err(c, "inode %lu has size %lld, but there are data at offset %lld",
		  (unsigned long)inode->i_ino, size,
		  ((loff_t)block) << UBIFS_BLOCK_SHIFT);
	mutex_unlock(&c->tnc_mutex);
	ubifs_dump_inode(c, inode);
	dump_stack();
	return -EINVAL;

out_unlock:
	mutex_unlock(&c->tnc_mutex);
	return err;
}
