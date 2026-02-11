ISMA_GetGPAC_KMS(ISMAEAPriv *priv, GF_Channel *ch, const char *kms_url)
{
	GF_Err e;
	FILE *t;
	GF_DownloadSession * sess;
	if (!strnicmp(kms_url, "(ipmp)", 6)) return GF_NOT_SUPPORTED;
	else if (!strnicmp(kms_url, "(uri)", 5)) kms_url += 5;
	else if (!strnicmp(kms_url, "file://", 7)) kms_url += 7;

	e = GF_OK;

	t = (strstr(kms_url, "://") == NULL) ? gf_f64_open(kms_url, "r") : NULL;
	if (t) {
		fclose(t);
		return gf_ismacryp_gpac_get_info(ch->esd->ESID, (char *)kms_url, priv->key, priv->salt);
	}


	GF_LOG(GF_LOG_INFO, GF_LOG_MEDIA, ("[ISMA E&A] Fetching ISMACryp key for channel %d\n", ch->esd->ESID) );

	sess = gf_term_download_new(ch->service, kms_url, 0, ISMA_KMS_NetIO, ch);
	if (!sess) return GF_IO_ERR;

	gf_dm_sess_process(sess);

	while (1) {
		e = gf_dm_sess_get_stats(sess, NULL, NULL, NULL, NULL, NULL, NULL);
		if (e) break;
	}
	if (e==GF_EOS) {
		e = gf_ismacryp_gpac_get_info(ch->esd->ESID, (char *) gf_dm_sess_get_cache_name(sess), priv->key, priv->salt);
	}
	gf_term_download_del(sess);
	return e;
}
