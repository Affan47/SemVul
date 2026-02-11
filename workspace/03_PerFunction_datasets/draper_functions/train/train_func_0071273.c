TCRYPT_get_data_offset(struct crypt_device *cd,
				 struct tcrypt_phdr *hdr,
				 struct crypt_params_tcrypt *params)
{
	uint64_t size;


	if (!hdr->d.version)
		goto hdr_offset;


	if (params->flags & CRYPT_TCRYPT_SYSTEM_HEADER)
		goto hdr_offset;

	if (params->mode && !strncmp(params->mode, "xts", 3)) {
		if (hdr->d.version < 3)
			return 1;

		if (params->flags & CRYPT_TCRYPT_HIDDEN_HEADER) {
			if (hdr->d.version > 3)
				return (hdr->d.mk_offset / hdr->d.sector_size);
			if (device_size(crypt_metadata_device(cd), &size) < 0)
				return 0;
			return (size - hdr->d.hidden_volume_size +
				(TCRYPT_HDR_HIDDEN_OFFSET_OLD)) / hdr->d.sector_size;
		}
		goto hdr_offset;
	}

	if (params->flags & CRYPT_TCRYPT_HIDDEN_HEADER) {
		if (device_size(crypt_metadata_device(cd), &size) < 0)
			return 0;
		return (size - hdr->d.hidden_volume_size +
			(TCRYPT_HDR_HIDDEN_OFFSET_OLD)) / hdr->d.sector_size;
	}

hdr_offset:
	return hdr->d.mk_offset / hdr->d.sector_size;
}
