parse_sec_desc(struct cifs_ntsd *pntsd, ssize_t acl_len, int raw)
{
	int rc;
	uint32_t dacloffset;
	char *end_of_acl = ((char *)pntsd) + acl_len;
	struct cifs_sid *owner_sid_ptr, *group_sid_ptr;
	struct cifs_ctrl_acl *dacl_ptr;

	if (pntsd == NULL)
		return -EIO;

	owner_sid_ptr = (struct cifs_sid *)((char *)pntsd +
				le32toh(pntsd->osidoffset));
	group_sid_ptr = (struct cifs_sid *)((char *)pntsd +
				le32toh(pntsd->gsidoffset));
	dacloffset = le32toh(pntsd->dacloffset);
	dacl_ptr = (struct cifs_ctrl_acl *)((char *)pntsd + dacloffset);
	printf("REVISION:0x%x\n", le16toh(pntsd->revision));
	printf("CONTROL:0x%x\n", le16toh(pntsd->type));

	rc = parse_sid(owner_sid_ptr, end_of_acl, "OWNER", raw);
	if (rc)
		return rc;

	rc = parse_sid(group_sid_ptr, end_of_acl, "GROUP", raw);
	if (rc)
		return rc;

	if (dacloffset)
		parse_dacl(dacl_ptr, end_of_acl, raw);
	else
		printf("No ACL\n");

	return 0;
}
