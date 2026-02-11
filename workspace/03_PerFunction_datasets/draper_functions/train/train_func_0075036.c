inode_link_to_lost_found(struct inode *inode)
{
	struct inode *base;
	struct user *admin;
	static char name[16 + 16 + 1];
	int name_len;

	base = inode_lookup_lost_found();
	if (base == NULL)
		return (GFARM_ERR_NO_SUCH_FILE_OR_DIRECTORY);
	admin = user_lookup(ADMIN_USER_NAME);
	if (admin == NULL)
		return (GFARM_ERR_NO_SUCH_USER);

	name_len = sizeof(name);
	snprintf(name, name_len, "%016llX%016llX",
	    (unsigned long long)inode->i_number,
	    (unsigned long long)inode->i_gen);
	return (inode_create_link_internal(base, name, admin, inode));
}
