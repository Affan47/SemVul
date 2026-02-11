gnome_keyring_attribute_list_append_uint32 (GnomeKeyringAttributeList *attributes,
                                            const char *name, guint32 value)
{
	GnomeKeyringAttribute attribute;

	g_return_if_fail (attributes);
	g_return_if_fail (name);

	attribute.name = g_strdup (name);
	attribute.type = GNOME_KEYRING_ATTRIBUTE_TYPE_UINT32;
	attribute.value.integer = value;
	g_array_append_val (attributes, attribute);
}
