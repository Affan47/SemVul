fillonedir(struct dir_context *ctx, const char *name, int namlen,
		      loff_t offset, u64 ino, unsigned int d_type)
{
	struct readdir_callback *buf =
		container_of(ctx, struct readdir_callback, ctx);
	struct old_linux_dirent __user * dirent;
	unsigned long d_ino;

	if (buf->result)
		return -EINVAL;
	d_ino = ino;
	if (sizeof(d_ino) < sizeof(ino) && d_ino != ino) {
		buf->result = -EOVERFLOW;
		return -EOVERFLOW;
	}
	buf->result++;
	dirent = buf->dirent;
	if (!access_ok(VERIFY_WRITE, dirent,
			(unsigned long)(dirent->d_name + namlen + 1) -
				(unsigned long)dirent))
		goto efault;
	if (	__put_user(d_ino, &dirent->d_ino) ||
		__put_user(offset, &dirent->d_offset) ||
		__put_user(namlen, &dirent->d_namlen) ||
		__copy_to_user(dirent->d_name, name, namlen) ||
		__put_user(0, dirent->d_name + namlen))
		goto efault;
	return 0;
efault:
	buf->result = -EFAULT;
	return -EFAULT;
}
