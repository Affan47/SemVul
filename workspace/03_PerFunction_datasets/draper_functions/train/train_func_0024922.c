calculate_name (GcrGnupgKey *self)
{
	GcrRecord* record;

	record = _gcr_records_find (self->pv->public_records, GCR_RECORD_SCHEMA_UID);
	g_return_val_if_fail (record, NULL);

	return _gcr_record_get_string (record, GCR_RECORD_UID_USERID);
}
