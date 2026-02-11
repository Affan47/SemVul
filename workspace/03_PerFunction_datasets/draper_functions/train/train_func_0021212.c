dumpctx_create(isc_mem_t *mctx, dns_db_t *db, dns_dbversion_t *version,
	       const dns_master_style_t *style, FILE *f, dns_dumpctx_t **dctxp,
	       dns_masterformat_t format, dns_masterrawheader_t *header)
{
	dns_dumpctx_t *dctx;
	isc_result_t result;
	unsigned int options;

	dctx = isc_mem_get(mctx, sizeof(*dctx));
	if (dctx == NULL)
		return (ISC_R_NOMEMORY);

	dctx->mctx = NULL;
	dctx->f = f;
	dctx->dbiter = NULL;
	dctx->db = NULL;
	dctx->version = NULL;
	dctx->done = NULL;
	dctx->done_arg = NULL;
	dctx->task = NULL;
	dctx->nodes = 0;
	dctx->first = ISC_TRUE;
	dctx->canceled = ISC_FALSE;
	dctx->file = NULL;
	dctx->tmpfile = NULL;
	dctx->format = format;
	if (header == NULL)
		dns_master_initrawheader(&dctx->header);
	else
		dctx->header = *header;

	switch (format) {
	case dns_masterformat_text:
		dctx->dumpsets = dump_rdatasets_text;
		break;
	case dns_masterformat_raw:
		dctx->dumpsets = dump_rdatasets_raw;
		break;
	case dns_masterformat_map:
		dctx->dumpsets = dump_rdatasets_map;
		break;
	default:
		INSIST(0);
		break;
	}

	result = totext_ctx_init(style, &dctx->tctx);
	if (result != ISC_R_SUCCESS) {
		UNEXPECTED_ERROR(__FILE__, __LINE__,
				 "could not set master file style");
		goto cleanup;
	}

	isc_stdtime_get(&dctx->now);
	dns_db_attach(db, &dctx->db);

	dctx->do_date = dns_db_iscache(dctx->db);

	if (dctx->format == dns_masterformat_text &&
	    (dctx->tctx.style.flags & DNS_STYLEFLAG_REL_OWNER) != 0) {
		options = DNS_DB_RELATIVENAMES;
	} else
		options = 0;
	result = dns_db_createiterator(dctx->db, options, &dctx->dbiter);
	if (result != ISC_R_SUCCESS)
		goto cleanup;

	result = isc_mutex_init(&dctx->lock);
	if (result != ISC_R_SUCCESS)
		goto cleanup;
	if (version != NULL)
		dns_db_attachversion(dctx->db, version, &dctx->version);
	else if (!dns_db_iscache(db))
		dns_db_currentversion(dctx->db, &dctx->version);
	isc_mem_attach(mctx, &dctx->mctx);
	dctx->references = 1;
	dctx->magic = DNS_DCTX_MAGIC;
	*dctxp = dctx;
	return (ISC_R_SUCCESS);

 cleanup:
	if (dctx->dbiter != NULL)
		dns_dbiterator_destroy(&dctx->dbiter);
	if (dctx->db != NULL)
		dns_db_detach(&dctx->db);
	if (dctx != NULL)
		isc_mem_put(mctx, dctx, sizeof(*dctx));
	return (result);
}
