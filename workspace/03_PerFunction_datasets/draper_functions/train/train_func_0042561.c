__ca_file_get_field_from_id (CaFileElementType type, guint64 db_id, const gchar *field)
{
	gchar ** aux;
	gchar * res;

	if (type == CA_FILE_ELEMENT_TYPE_CERT) {
		aux = __ca_file_get_single_row (ca_db, "SELECT %s FROM certificates WHERE id=%" GNOMINT_GUINT64_FORMAT ";", field, db_id);
	} else {
		aux = __ca_file_get_single_row (ca_db, "SELECT %s FROM cert_requests WHERE id=%" GNOMINT_GUINT64_FORMAT ";", field, db_id);
	}

	if (! aux)
		return NULL;

	if (! aux[0]) {
		g_strfreev (aux);
		return NULL;
	}

	res = g_strdup (aux[0]);

	g_strfreev (aux);

	return res;

}
