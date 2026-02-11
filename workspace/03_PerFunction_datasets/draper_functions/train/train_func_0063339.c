OMA_DRM_Setup(ISMAEAPriv *priv, GF_IPMPEvent *evt)
{
	u32 hdr_pos;
	GF_OMADRM2Config *cfg = (GF_OMADRM2Config*)evt->config_data;

	priv->state = ISMAEA_STATE_ERROR;

	if (cfg->scheme_type != GF_4CC('o','d','k','m')) return GF_NOT_SUPPORTED;
	if (cfg->scheme_version != 0x00000200) return GF_NOT_SUPPORTED;

	hdr_pos = 0;
	while (hdr_pos<cfg->oma_drm_textual_headers_len) {
		u32 len;
		char *sep;
		if (!strncmp(cfg->oma_drm_textual_headers + hdr_pos, "PreviewRange", 12)) {
			sep = strchr(cfg->oma_drm_textual_headers + hdr_pos, ':');
			if (sep) priv->preview_range = atoi(sep+1);
		}
		len = strlen(cfg->oma_drm_textual_headers + hdr_pos);
		hdr_pos += len+1;
	}
	priv->is_oma = 1;


	if (!cfg->kms_uri) return GF_NON_COMPLIANT_BITSTREAM;
	priv->state = ISMAEA_STATE_SETUP;


	if (priv->preview_range) return GF_OK;
	return GF_NOT_SUPPORTED;
}
