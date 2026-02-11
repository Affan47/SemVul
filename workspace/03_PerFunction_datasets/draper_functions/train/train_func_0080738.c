get_client_id (soap, uid, gid)
struct soap *soap;
uid_t *uid;
gid_t *gid;
{
	struct passwd *pw;
	char username[CA_MAXUSRNAMELEN+1];

	if (get_client_username (soap, username, sizeof(username)) < 0)
		return (-1);
	if ((pw = Cgetpwnam (username)) == NULL)
		return (-1);
	*uid = pw->pw_uid;
	*gid = pw->pw_gid;
	return (0);
}
