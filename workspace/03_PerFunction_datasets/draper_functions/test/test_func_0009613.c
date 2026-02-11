au_refresh_i(struct super_block *sb, unsigned int do_idop)
{
	int err, e;
	unsigned int sigen;
	unsigned long long max, ull;
	struct inode *inode, **array;

	array = au_iarray_alloc(sb, &max);
	err = PTR_ERR(array);
	if (IS_ERR(array))
		goto out;

	err = 0;
	sigen = au_sigen(sb);
	for (ull = 0; ull < max; ull++) {
		inode = array[ull];
		if (unlikely(!inode))
			break;

		e = 0;
		ii_write_lock_child(inode);
		if (au_iigen(inode, NULL) != sigen) {
			e = au_refresh_hinode_self(inode);
			if (unlikely(e)) {
				au_refresh_iop(inode, 1);
				pr_err("error %d, i%lu\n", e, inode->i_ino);
				if (!err)
					err = e;

			}
		}
		if (!e && do_idop)
			au_refresh_iop(inode, 0);
		ii_write_unlock(inode);
	}

	au_iarray_free(array, max);

out:
	return err;
}
