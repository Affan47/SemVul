ews_decode_addressbook_write_display_type (EContact **contact,
					   guint32 value,
					   gboolean extended)
{
	EVCardAttribute *attr;
	const gchar *display_type;

	if (extended)
		display_type = ews_decode_addressbook_get_display_type_extended (value);
	else
		display_type = ews_decode_addressbook_get_display_type (value);

	if (display_type != NULL) {
		attr = e_vcard_attribute_new (NULL, "X-EWS-KIND");
		e_vcard_add_attribute_with_value (E_VCARD (*contact), attr, display_type);
	}
}
