ews_message_add_extended_property_distinguished_tag (ESoapMessage *msg,
						     const gchar *set_id,
						     guint32 prop_id,
						     EEwsMessageDataType data_type,
						     gconstpointer value)
{
	const gchar *prop_type = e_ews_message_data_type_get_xml_name (data_type);

	g_return_if_fail (prop_type != NULL);

	e_soap_message_start_element (msg, "ExtendedProperty", NULL, NULL);

	e_ews_message_write_extended_distinguished_tag (msg, set_id, prop_id, prop_type);
	ews_message_write_data_value (msg, data_type, value);

	e_soap_message_end_element (msg);
}
