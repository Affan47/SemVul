_add_type_param_from_google_rel (EVCardAttribute *attr,
                                 const struct RelTypeMap rel_type_map[],
                                 guint map_len,
                                 const gchar *rel)
{
	const gchar * field;
	guint i;

	field = strstr (rel ? rel : "", "#");
	if (NULL == field)
		return FALSE;

	field++;
	for (i = 0; i < map_len; i++) {
		if (0 == g_ascii_strcasecmp (rel_type_map[i].rel, field)) {
			EVCardAttributeParam *param;
			param = e_vcard_attribute_param_new ("TYPE");
			e_vcard_attribute_param_add_value (param, rel_type_map[i].types[0]);
			if (rel_type_map[i].types[1])
				e_vcard_attribute_param_add_value (param, rel_type_map[i].types[1]);
			e_vcard_attribute_add_param (attr, param);
			return TRUE;
		}
	}
	g_warning ("Unknown relationship '%s'", rel);

	return TRUE;
}
