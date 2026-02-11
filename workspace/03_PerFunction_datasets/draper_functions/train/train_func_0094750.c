ggept_gtkgv_extract(const extvec_t *exv, struct ggep_gtkgv *info)
{
	const char *p;
	int tlen;
	ggept_status_t status = GGEP_OK;

	g_assert(exv->ext_type == EXT_GGEP);
	g_assert(exv->ext_token == EXT_T_GGEP_GTKGV);

	tlen = ext_paylen(exv);


	if (tlen < 13)
		return GGEP_INVALID;

	p = ext_payload(exv);

	info->version = p[0];
	info->major = p[1];
	info->minor = p[2];
	info->patch = p[3];
	info->revchar = p[4];
	info->release = peek_be32(&p[5]);
	info->build = peek_be32(&p[9]);

	info->dirty = FALSE;
	info->commit_len = 0;
	ZERO(&info->commit);
	info->osname = NULL;

	if (info->version >= 1) {
		bstr_t *bs;
		uint8 flags;

		bs = bstr_open(p, tlen, GNET_PROPERTY(ggep_debug) ? BSTR_F_ERROR : 0);
		bstr_skip(bs, 13);

		if (bstr_read_u8(bs, &flags)) {
			uint8 aflags = flags;


			while ((aflags & GTKGV_F_CONT) && bstr_read_u8(bs, &aflags))
				;


			info->dirty = booleanize(aflags & GTKGV_F_DIRTY);


			if (aflags & GTKGV_F_GIT) {
				if (
					bstr_read_u8(bs, &info->commit_len) &&
					info->commit_len != 0
				) {
					if (info->commit_len <= 2 * SHA1_RAW_SIZE) {
						uint8 bytes = (info->commit_len + 1) / 2;
						if (!bstr_read(bs, &info->commit, bytes)) {
							status = GGEP_INVALID;
						}
					} else {
						status = GGEP_INVALID;
					}
				}
			}


			if ((aflags & GTKGV_F_OS) && GGEP_OK == status) {
				uint8 value;

				if (bstr_read_u8(bs, &value)) {
					info->osname = ggept_gtkgv_osname(value);
				}
			}
		}

		bstr_free(&bs);
	}

	return status;
}
