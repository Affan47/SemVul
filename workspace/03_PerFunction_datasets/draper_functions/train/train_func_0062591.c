set_nonunix_perms(unsigned int * mode, struct afp_file_info *fp)
{
	if (fp->isdir)
		*mode = 0700 | S_IFDIR;
	else
		*mode = 0600 | S_IFREG;
}
