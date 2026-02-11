afs_dir_iterate(struct inode *dir, struct dir_context *ctx,
			   struct key *key)
{
	union afs_dir_block *dblock;
	struct afs_dir_page *dbuf;
	struct page *page;
	unsigned blkoff, limit;
	int ret;

	_enter("{%lu},%u,,", dir->i_ino, (unsigned)ctx->pos);

	if (test_bit(AFS_VNODE_DELETED, &AFS_FS_I(dir)->flags)) {
		_leave(" = -ESTALE");
		return -ESTALE;
	}


	ctx->pos += sizeof(union afs_dirent) - 1;
	ctx->pos &= ~(sizeof(union afs_dirent) - 1);


	ret = 0;
	while (ctx->pos < dir->i_size) {
		blkoff = ctx->pos & ~(sizeof(union afs_dir_block) - 1);


		page = afs_dir_get_page(dir, blkoff / PAGE_SIZE, key);
		if (IS_ERR(page)) {
			ret = PTR_ERR(page);
			break;
		}

		limit = blkoff & ~(PAGE_SIZE - 1);

		dbuf = page_address(page);


		do {
			dblock = &dbuf->blocks[(blkoff % PAGE_SIZE) /
					       sizeof(union afs_dir_block)];
			ret = afs_dir_iterate_block(ctx, dblock, blkoff);
			if (ret != 1) {
				afs_dir_put_page(page);
				goto out;
			}

			blkoff += sizeof(union afs_dir_block);

		} while (ctx->pos < dir->i_size && blkoff < limit);

		afs_dir_put_page(page);
		ret = 0;
	}

out:
	_leave(" = %d", ret);
	return ret;
}
