decode_param_list (const char *in)
{
	struct _rfc2184_param *rfc2184, *list, *t;
	GMimeParam *param, *params, *tail;
	struct _rfc2184_part *part;
	GHashTable *rfc2184_hash;
	const char *inptr = in;
	char *name, *value;
	gboolean encoded;
	GString *gvalue;
	guint i;
	int id;

	params = NULL;
	tail = (GMimeParam *) &params;

	list = NULL;
	t = (struct _rfc2184_param *) &list;
	rfc2184_hash = g_hash_table_new (g_mime_strcase_hash, g_mime_strcase_equal);

	decode_lwsp (&inptr);

	do {

		if (!decode_param (&inptr, &name, &value, &id, &encoded)) {
			decode_lwsp (&inptr);

			if (*inptr == ';')
				continue;

			break;
		}

		if (id != -1) {

			if (!(rfc2184 = g_hash_table_lookup (rfc2184_hash, name))) {
				rfc2184 = rfc2184_param_new (name, value, id, encoded);
				param = rfc2184->param;
				t->next = rfc2184;
				t = rfc2184;

				g_hash_table_insert (rfc2184_hash, param->name, rfc2184);

				tail->next = param;
				tail = param;
			} else {
				rfc2184_param_add_part (rfc2184, value, id, encoded);
				g_free (name);
			}
		} else {
			param = g_new (GMimeParam, 1);
			param->next = NULL;
			param->name = name;

			if (encoded) {

				param->value = rfc2184_decode (value);
				g_free (value);
			} else {

				param->value = value;
			}

			tail->next = param;
			tail = param;
		}

		decode_lwsp (&inptr);
	} while (*inptr++ == ';');

	g_hash_table_destroy (rfc2184_hash);

	rfc2184 = list;
	while (rfc2184 != NULL) {
		t = rfc2184->next;

		param = rfc2184->param;
		gvalue = g_string_new ("");

		g_ptr_array_sort (rfc2184->parts, rfc2184_sort_cb);
		for (i = 0; i < rfc2184->parts->len; i++) {
			part = rfc2184->parts->pdata[i];
			g_string_append (gvalue, part->value);
			g_free (part->value);
			g_free (part);
		}

		g_ptr_array_free (rfc2184->parts, TRUE);

		param->value = charset_convert (rfc2184->charset, gvalue->str, gvalue->len);
		g_string_free (gvalue, FALSE);

		g_free (rfc2184->lang);
		g_free (rfc2184);
		rfc2184 = t;
	}

	return params;
}
