check_ea_in_inode(e2fsck_t ctx, struct problem_context *pctx)
{
	struct ext2_super_block *sb = ctx->fs->super;
	struct ext2_inode_large *inode;
	struct ext2_ext_attr_entry *entry;
	char *start, *end;
	unsigned int storage_size, remain;
	int problem = 0;

	inode = (struct ext2_inode_large *) pctx->inode;
	storage_size = EXT2_INODE_SIZE(ctx->fs->super) - EXT2_GOOD_OLD_INODE_SIZE -
		inode->i_extra_isize;
	start = ((char *) inode) + EXT2_GOOD_OLD_INODE_SIZE +
		inode->i_extra_isize + sizeof(__u32);
	end = (char *) inode + EXT2_INODE_SIZE(ctx->fs->super);
	entry = (struct ext2_ext_attr_entry *) start;


	remain = storage_size - sizeof(__u32);

	while (!EXT2_EXT_IS_LAST_ENTRY(entry)) {
		__u32 hash;


		remain -= sizeof(struct ext2_ext_attr_entry);


		if (EXT2_EXT_ATTR_SIZE(entry->e_name_len) > remain) {
			pctx->num = entry->e_name_len;
			problem = PR_1_ATTR_NAME_LEN;
			goto fix;
		}


		remain -= EXT2_EXT_ATTR_SIZE(entry->e_name_len);


		if (entry->e_value_size == 0 || entry->e_value_size > remain) {
			pctx->num = entry->e_value_size;
			problem = PR_1_ATTR_VALUE_SIZE;
			goto fix;
		}


		if (entry->e_value_block != 0) {
			pctx->num = entry->e_value_block;
			problem = PR_1_ATTR_VALUE_BLOCK;
			goto fix;
		}

		hash = ext2fs_ext_attr_hash_entry(entry,
						  start + entry->e_value_offs);


		if (entry->e_hash != 0 && entry->e_hash != hash) {
			pctx->num = entry->e_hash;
			problem = PR_1_ATTR_HASH;
			goto fix;
		}

		remain -= entry->e_value_size;

		entry = EXT2_EXT_ATTR_NEXT(entry);
	}
fix:


	if (problem == 0 || !fix_problem(ctx, problem, pctx))
		return;


	*((__u32 *)start) = 0UL;
	e2fsck_write_inode_full(ctx, pctx->ino, pctx->inode,
				EXT2_INODE_SIZE(sb), "pass1");
}
