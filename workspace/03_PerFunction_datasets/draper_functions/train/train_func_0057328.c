fuse_fs_releasedir(struct fuse_fs *fs, const char *path,
		       struct fuse_file_info *fi)
{
	fuse_get_context()->private_data = fs->user_data;
	if (fs->op.releasedir) {
		if (fs->debug)
			fprintf(stderr, "releasedir[%llu] flags: 0x%x\n",
				(unsigned long long) fi->fh, fi->flags);

		return fs->op.releasedir(path, fi);
	} else {
		return 0;
	}
}
