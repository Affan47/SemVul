LUKS_hdr_uuid_set(
	struct luks_phdr *hdr,
	const char *uuid,
	struct crypt_device *ctx)
{
	uuid_t partitionUuid;

	if (uuid && uuid_parse(uuid, partitionUuid) == -1) {
		log_err(ctx, _("Wrong LUKS UUID format provided.\n"));
		return -EINVAL;
	}
	if (!uuid)
		uuid_generate(partitionUuid);

	uuid_unparse(partitionUuid, hdr->uuid);

	return LUKS_write_phdr(hdr, ctx);
}
