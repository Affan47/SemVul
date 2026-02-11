isvalid_attrname(const char *attrname)
{
	int namelen = strlen(attrname);

	return ((0 < namelen) && (namelen <= MAX_XATTR_NAME_LEN));
}
