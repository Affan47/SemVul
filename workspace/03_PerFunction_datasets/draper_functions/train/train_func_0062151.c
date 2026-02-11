couldbe_mf_symlink(const struct cifs_fattr *fattr)
{
	if (!S_ISREG(fattr->cf_mode))

		return false;

	if (fattr->cf_eof != CIFS_MF_SYMLINK_FILE_SIZE)

		return false;

	return true;
}
