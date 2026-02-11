crypt_get_uuid(struct crypt_device *cd)
{
	if (isLUKS(cd->type))
		return cd->u.luks1.hdr.uuid;

	if (isVERITY(cd->type))
		return cd->u.verity.uuid;

	return NULL;
}
