write_file(struct open_file *ofile, const char *buf, size_t len, off_t off)
{
	int retv;

	lock_file(ofile);
	if (S_ISDIR(ofile->dentry->ddent->mode))
		retv = write_dir(ofile, buf, len, off);
	else
		retv = rw_file(ofile, (char *)buf, len, off, 0);
	unlock_file(ofile);

	return retv;
}
