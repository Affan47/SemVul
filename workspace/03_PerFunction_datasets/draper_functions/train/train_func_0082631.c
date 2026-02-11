git_odb__error_notfound(const char *message, const git_oid *oid)
{
	if (oid != NULL) {
		char oid_str[GIT_OID_HEXSZ + 1];
		git_oid_tostr(oid_str, sizeof(oid_str), oid);
		giterr_set(GITERR_ODB, "Object not found - %s (%s)", message, oid_str);
	} else
		giterr_set(GITERR_ODB, "Object not found - %s", message);

	return GIT_ENOTFOUND;
}
