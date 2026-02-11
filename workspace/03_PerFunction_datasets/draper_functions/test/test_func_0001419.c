glue_open(VOID *intf, CHAR16 *name, fops_fd_t *fd)
{
	netfs_interface_t *netfs = (netfs_interface_t *)intf;
	CHAR16 fullname[FILENAME_MAXLEN];

	if (name[0] != CHAR_SLASH && name[0] != CHAR_BACKSLASH && netfs_default_path[0] != CHAR_NULL) {
		if (StrLen(netfs_default_path) + StrLen(name) + 1 >= FILENAME_MAXLEN)
			return EFI_INVALID_PARAMETER;

		StrCpy(fullname, netfs_default_path);
		StrCat(fullname, name);
		name = fullname;
	}
	return netfs->netfs_open(intf, name, fd);
}
