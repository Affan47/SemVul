e2fsck_add_dir_info(e2fsck_t ctx, ext2_ino_t ino, ext2_ino_t parent)
{
	struct dir_info_db 	*db;
	struct dir_info 	*dir, ent;
	int			i, j;
	errcode_t		retval;
	unsigned long		old_size;

#ifdef DIRINFO_DEBUG
	printf("add_dir_info for inode (%lu, %lu)...\n", ino, parent);
#endif
	if (!ctx->dir_info)
		setup_db(ctx);
	db = ctx->dir_info;

	if (ctx->dir_info->count >= ctx->dir_info->size) {
		old_size = ctx->dir_info->size * sizeof(struct dir_info);
		ctx->dir_info->size += 10;
		retval = ext2fs_resize_mem(old_size, ctx->dir_info->size *
					   sizeof(struct dir_info),
					   &ctx->dir_info->array);
		if (retval) {
			ctx->dir_info->size -= 10;
			return;
		}
	}

	ent.ino = ino;
	ent.parent = parent;
	ent.dotdot = parent;

	if (db->tdb) {
		e2fsck_put_dir_info(ctx, &ent);
		return;
	}


	if (ctx->dir_info->count &&
	    ctx->dir_info->array[ctx->dir_info->count-1].ino >= ino) {
		for (i = ctx->dir_info->count-1; i > 0; i--)
			if (ctx->dir_info->array[i-1].ino < ino)
				break;
		dir = &ctx->dir_info->array[i];
		if (dir->ino != ino)
			for (j = ctx->dir_info->count++; j > i; j--)
				ctx->dir_info->array[j] = ctx->dir_info->array[j-1];
	} else
		dir = &ctx->dir_info->array[ctx->dir_info->count++];

	dir->ino = ino;
	dir->dotdot = parent;
	dir->parent = parent;
}
