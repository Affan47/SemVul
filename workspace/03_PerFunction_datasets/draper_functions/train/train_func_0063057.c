get_methodref_signature (MonoImage *m, guint32 blob_signature, const char *fancy_name)
{
	GString *res = g_string_new ("");
	const char *ptr = mono_metadata_blob_heap (m, blob_signature);
	char *allocated_ret_type, *s;
	const char *cconv_str;
	gboolean seen_vararg = 0;
	int param_count;
	int i, gen_count = 0;
	int cconv;

	 mono_metadata_decode_value (ptr, &ptr);

	if (*ptr & 0x20){
		if (*ptr & 0x40)
			g_string_append (res, "explicit-this ");
		else
			g_string_append (res, "instance ");
	}

	if (*ptr & 0x10)
		gen_count = 1;
	cconv = *ptr & 0x0f;
	cconv_str = map (cconv, call_conv_type_map);
	if (strcmp (cconv_str, "default") != 0) {
		g_string_append (res, cconv_str);
		g_string_append (res, " ");
	}

	ptr++;
	if (gen_count)
		gen_count = mono_metadata_decode_value (ptr, &ptr);
	param_count = mono_metadata_decode_value (ptr, &ptr);
	if (cconv != 0xa) {
		ptr = get_ret_type (m, ptr, &allocated_ret_type, NULL);
		g_string_append (res, allocated_ret_type);
		g_free (allocated_ret_type);
	}

	if (fancy_name){
		g_string_append_c (res, ' ');
		g_string_append (res, fancy_name);
	}

	g_string_append (res, "(");


	for (i = 0; i < param_count; i++){
		char *param = NULL;


		if (*ptr == 0x41){
			if (!seen_vararg){
				g_string_append (res, "..., ");
				seen_vararg = 1;
			}

			ptr++;
		}

		ptr = get_param (m, ptr, &param, NULL);
		g_string_append (res, param);
		if (i+1 != param_count)
			g_string_append (res, ", ");
		g_free (param);
	}
	g_string_append (res, ")");


	s = res->str;
	g_string_free (res, FALSE);
	return s;
}
