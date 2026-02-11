camel_content_type_simple (CamelContentType *ct)
{
	if (ct->type == NULL) {
		w (g_warning ("Content-Type with no main type"));
		return g_strdup ("text/plain");
	} else if (ct->subtype == NULL) {
		w (g_warning ("Content-Type with no sub type: %s", ct->type));
		if (!g_ascii_strcasecmp (ct->type, "multipart"))
			return g_strdup_printf ("%s/mixed", ct->type);
		else
			return g_strdup (ct->type);
	} else
		return g_strdup_printf ("%s/%s", ct->type, ct->subtype);
}
