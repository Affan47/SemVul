local_summary_encode_x_evolution (CamelLocalSummary *cls,
                                  const CamelLocalMessageInfo *mi)
{
	GString *out = g_string_new ("");
	struct _camel_header_param *params = NULL;
	CamelFlag *flag = mi->info.user_flags;
	CamelTag *tag = mi->info.user_tags;
	gchar *ret;
	const gchar *p, *uidstr;
	guint32 uid;


	p = uidstr = camel_message_info_uid (mi);
	while (*p && isdigit (*p))
		p++;
	if (*p == 0 && sscanf (uidstr, "%u", &uid) == 1) {
		g_string_printf (out, "%08x-%04x", uid, mi->info.flags & 0xffff);
	} else {
		g_string_printf (out, "%s-%04x", uidstr, mi->info.flags & 0xffff);
	}

	if (flag || tag) {
		GString *val = g_string_new ("");

		if (flag) {
			while (flag) {
				g_string_append (val, flag->name);
				if (flag->next)
					g_string_append_c (val, ',');
				flag = flag->next;
			}
			camel_header_set_param (&params, "flags", val->str);
			g_string_truncate (val, 0);
		}
		if (tag) {
			while (tag) {
				g_string_append (val, tag->name);
				g_string_append_c (val, '=');
				g_string_append (val, tag->value);
				if (tag->next)
					g_string_append_c (val, ',');
				tag = tag->next;
			}
			camel_header_set_param (&params, "tags", val->str);
		}
		g_string_free (val, TRUE);
		camel_header_param_list_format_append (out, params);
		camel_header_param_list_free (params);
	}
	ret = out->str;
	g_string_free (out, FALSE);

	return ret;
}
