warnif_cond_requires_resp(const struct acl_cond *cond, const char *file, int line)
{
	struct acl *acl;

	if (!cond || !(cond->requires & ACL_USE_RTR_ANY))
		return 0;

	acl = cond_find_require(cond, ACL_USE_RTR_ANY);
	Warning("parsing [%s:%d] : acl '%s' involves some response-only criteria which will be ignored.\n",
		file, line, acl ? acl->name : "(unknown)");
	return ERR_WARN;
}
