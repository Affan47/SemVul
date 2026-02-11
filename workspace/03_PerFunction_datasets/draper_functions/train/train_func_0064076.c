entry_new (adcli_conn *conn,
           const char *object_class,
           entry_builder builder,
           const char *sam_name)
{
	adcli_entry *entry;

	entry = calloc (1, sizeof (adcli_entry));
	return_val_if_fail (entry != NULL, NULL);

	entry->conn = adcli_conn_ref (conn);
	entry->refs = 1;

	entry->sam_name = strdup (sam_name);
	return_val_if_fail (entry->sam_name != NULL, NULL);

	entry->builder = builder;
	entry->object_class = object_class;
	return entry;
}
