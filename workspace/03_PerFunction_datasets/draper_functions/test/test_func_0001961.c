get_acl_callback(const char *w, int f, void *dummy)
{
	struct get_acl *ga=(struct get_acl *)dummy;

	if (addrcmp(w, ga->who) == 0)
		ga->flags=f;
	return (0);
}
