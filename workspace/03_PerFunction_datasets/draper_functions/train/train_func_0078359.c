rfc2184_param_add_part (struct _rfc2184_param *rfc2184, char *value, int id, gboolean encoded)
{
	struct _rfc2184_part *part;
	size_t len;

	part = g_new (struct _rfc2184_part, 1);
	g_ptr_array_add (rfc2184->parts, part);
	part->id = id;

	if (encoded) {
		len = strlen (value);
		part->value = g_malloc (len + 1);
		hex_decode (value, len, part->value);
		g_free (value);
	} else {
		part->value = value;
	}
}
