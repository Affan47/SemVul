photo_getter (EContact *contact,
              EVCardAttribute *attr)
{
	GList *values;

	if (!attr)
		return NULL;

	values = e_vcard_attribute_get_param (attr, EVC_ENCODING);
	if (values && (g_ascii_strcasecmp (values->data, "b") == 0 ||

		       g_ascii_strcasecmp (values->data, "base64") == 0)) {
		values = e_vcard_attribute_get_values_decoded (attr);
		if (values && values->data) {
			GString *s = values->data;
			EContactPhoto *photo;

			if (!s->len)
				return NULL;

			photo = g_new0 (EContactPhoto, 1);
			photo->type = E_CONTACT_PHOTO_TYPE_INLINED;
			photo->data.inlined.length = s->len;
			photo->data.inlined.data = g_malloc (photo->data.inlined.length);
			memcpy (photo->data.inlined.data, s->str, photo->data.inlined.length);

			values = e_vcard_attribute_get_param (attr, EVC_TYPE);
			if (values && values->data)
				photo->data.inlined.mime_type = g_strdup_printf ("image/%s", (gchar *) values->data);
			return photo;
		}
	}

	values = e_vcard_attribute_get_param (attr, EVC_VALUE);
	if (values && g_ascii_strcasecmp (values->data, "uri") == 0) {
		EContactPhoto *photo;
		photo = g_new0 (EContactPhoto, 1);
		photo->type = E_CONTACT_PHOTO_TYPE_URI;
		photo->data.uri = e_vcard_attribute_get_value (attr);
		return photo;
	}
	return NULL;
}
