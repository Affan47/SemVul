build_avpair_blob(struct cifs_ses *ses, const struct nls_table *nls_cp)
{
	unsigned int dlen;
	unsigned int size = 2 * sizeof(struct ntlmssp2_name);
	char *defdmname = "WORKGROUP";
	unsigned char *blobptr;
	struct ntlmssp2_name *attrptr;

	if (!ses->domainName) {
		ses->domainName = kstrdup(defdmname, GFP_KERNEL);
		if (!ses->domainName)
			return -ENOMEM;
	}

	dlen = strlen(ses->domainName);


	ses->auth_key.len = size + 2 * dlen;
	ses->auth_key.response = kzalloc(ses->auth_key.len, GFP_KERNEL);
	if (!ses->auth_key.response) {
		ses->auth_key.len = 0;
		return -ENOMEM;
	}

	blobptr = ses->auth_key.response;
	attrptr = (struct ntlmssp2_name *) blobptr;


	attrptr->type = cpu_to_le16(NTLMSSP_AV_NB_DOMAIN_NAME);
	attrptr->length = cpu_to_le16(2 * dlen);
	blobptr = (unsigned char *)attrptr + sizeof(struct ntlmssp2_name);
	cifs_strtoUTF16((__le16 *)blobptr, ses->domainName, dlen, nls_cp);

	return 0;
}
