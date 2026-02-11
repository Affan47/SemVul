ast_rtp_dtls_cfg_parse(struct ast_rtp_dtls_cfg *dtls_cfg, const char *name, const char *value)
{
	if (!strcasecmp(name, "dtlsenable")) {
		dtls_cfg->enabled = ast_true(value) ? 1 : 0;
	} else if (!strcasecmp(name, "dtlsverify")) {
		dtls_cfg->verify = ast_true(value) ? 1 : 0;
	} else if (!strcasecmp(name, "dtlsrekey")) {
		if (sscanf(value, "%30u", &dtls_cfg->rekey) != 1) {
			return -1;
		}
	} else if (!strcasecmp(name, "dtlscertfile")) {
		ast_free(dtls_cfg->certfile);
		dtls_cfg->certfile = ast_strdup(value);
	} else if (!strcasecmp(name, "dtlsprivatekey")) {
		ast_free(dtls_cfg->pvtfile);
		dtls_cfg->pvtfile = ast_strdup(value);
	} else if (!strcasecmp(name, "dtlscipher")) {
		ast_free(dtls_cfg->cipher);
		dtls_cfg->cipher = ast_strdup(value);
	} else if (!strcasecmp(name, "dtlscafile")) {
		ast_free(dtls_cfg->cafile);
		dtls_cfg->cafile = ast_strdup(value);
	} else if (!strcasecmp(name, "dtlscapath") || !strcasecmp(name, "dtlscadir")) {
		ast_free(dtls_cfg->capath);
		dtls_cfg->capath = ast_strdup(value);
	} else if (!strcasecmp(name, "dtlssetup")) {
		if (!strcasecmp(value, "active")) {
			dtls_cfg->default_setup = AST_RTP_DTLS_SETUP_ACTIVE;
		} else if (!strcasecmp(value, "passive")) {
			dtls_cfg->default_setup = AST_RTP_DTLS_SETUP_PASSIVE;
		} else if (!strcasecmp(value, "actpass")) {
			dtls_cfg->default_setup = AST_RTP_DTLS_SETUP_ACTPASS;
		}
	} else {
		return -1;
	}

	return 0;
}
