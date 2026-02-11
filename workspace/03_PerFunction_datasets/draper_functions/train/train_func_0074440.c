dquot_file_open(struct inode *inode, struct file *file)
{
	int error;

	error = generic_file_open(inode, file);
	if (!error && (file->f_mode & FMODE_WRITE))
		dquot_initialize(inode);
	return error;
}
