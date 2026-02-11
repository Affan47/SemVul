normalize_key_records (GPtrArray *records)
{
	GQuark schema;
	guchar trust = 0;
	const gchar *prev;
	gboolean force = FALSE;
	guint i;

	if (records->len == 0)
		return;

	schema = _gcr_record_get_schema (records->pdata[0]);
	if (schema == GCR_RECORD_SCHEMA_PUB) {

		if (check_key_expiry (records->pdata[0])) {
			trust = 'e';
			force = TRUE;


		} else {
			normalize_capabilities (records);
			trust = 'o';
			force = FALSE;
		}


		_gcr_record_set_char (records->pdata[0], GCR_RECORD_KEY_OWNERTRUST, 'o');

	} else if (schema == GCR_RECORD_SCHEMA_SEC) {


		trust = 0;
		force = FALSE;
	}


	if (trust != 0) {
		for (i = 0; i < records->len; i++) {
			if (!force) {
				prev = _gcr_record_get_raw (records->pdata[i], GCR_RECORD_TRUST);
				if (prev != NULL && prev[0])
					continue;
			}
			schema = _gcr_record_get_schema (records->pdata[i]);
			if (schema != GCR_RECORD_SCHEMA_SIG && schema != GCR_RECORD_SCHEMA_FPR)
				_gcr_record_set_char (records->pdata[i], GCR_RECORD_TRUST, trust);
		}
	}
}
