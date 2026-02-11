jffs2_readdir(struct file *file, struct dir_context *ctx)
{
	struct inode *inode = file_inode(file);
	struct jffs2_inode_info *f = JFFS2_INODE_INFO(inode);
	struct jffs2_full_dirent *fd;
	unsigned long curofs = 1;

	jffs2_dbg(1, "jffs2_readdir() for dir_i #%lu\n", inode->i_ino);

	if (!dir_emit_dots(file, ctx))
		return 0;

	mutex_lock(&f->sem);
	for (fd = f->dents; fd; fd = fd->next) {
		curofs++;

		if (curofs < ctx->pos) {
			jffs2_dbg(2, "Skipping dirent: \"%s\", ino #%u, type %d, because curofs %ld < offset %ld\n",
				  fd->name, fd->ino, fd->type, curofs, (unsigned long)ctx->pos);
			continue;
		}
		if (!fd->ino) {
			jffs2_dbg(2, "Skipping deletion dirent \"%s\"\n",
				  fd->name);
			ctx->pos++;
			continue;
		}
		jffs2_dbg(2, "Dirent %ld: \"%s\", ino #%u, type %d\n",
			  (unsigned long)ctx->pos, fd->name, fd->ino, fd->type);
		if (!dir_emit(ctx, fd->name, strlen(fd->name), fd->ino, fd->type))
			break;
		ctx->pos++;
	}
	mutex_unlock(&f->sem);
	return 0;
}
