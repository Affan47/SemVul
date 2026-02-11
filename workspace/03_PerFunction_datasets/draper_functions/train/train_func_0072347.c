parse (EVCard *evc,
       const gchar *str,
       gboolean ignore_uid)
{
	gchar *buf;
	gchar *p;
	EVCardAttribute *attr;

	buf = make_valid_utf8 (str);

	d (printf ("BEFORE FOLDING:\n"));
	d (printf (str));
	d (printf ("\n\nAFTER FOLDING:\n"));
	d (printf (buf));

	p = buf;

	attr = read_attribute (&p);
	if (!attr || attr->group || g_ascii_strcasecmp (attr->name, "begin")) {
		g_warning ("vcard began without a BEGIN:VCARD\n");
	}
	if (attr && !g_ascii_strcasecmp (attr->name, "begin")) {
		e_vcard_attribute_free (attr);
		attr = NULL;
	} else if (attr) {
		if (!ignore_uid || g_ascii_strcasecmp (attr->name, EVC_UID) != 0)
			e_vcard_add_attribute (evc, attr);
	}
	while (*p) {
		EVCardAttribute *next_attr = read_attribute (&p);

		if (next_attr) {
			attr = next_attr;

			if (g_ascii_strcasecmp (next_attr->name, "end") == 0)
				break;

			if (ignore_uid && g_ascii_strcasecmp (attr->name, EVC_UID) == 0) {
				e_vcard_attribute_free (attr);
				attr = NULL;
				continue;
			}

			e_vcard_add_attribute (evc, next_attr);
		}
	}

	if (!attr || attr->group || g_ascii_strcasecmp (attr->name, "end")) {
		g_warning ("vcard ended without END:VCARD\n");
	}

	if (attr && !g_ascii_strcasecmp (attr->name, "end"))
		e_vcard_attribute_free (attr);

	g_free (buf);

	evc->priv->attributes = g_list_reverse (evc->priv->attributes);
}
