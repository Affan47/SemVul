dump_cattrs_for_type_params (MonoImage *m, guint32 token, const char *indent)
{
	MonoTableInfo *tdef  = &m->tables [MONO_TABLE_GENERICPARAM];
	guint32 cols [MONO_GENERICPARAM_SIZE];
	guint32 owner = 0, i;
	GList *list = NULL;

	if (! (i = mono_metadata_get_generic_param_row (m, token, &owner)))
		return;

	mono_metadata_decode_row (tdef, i - 1, cols, MONO_GENERICPARAM_SIZE);
	do {
		list = dis_get_custom_attrs (m, mono_metadata_make_token (MONO_TABLE_GENERICPARAM, i));
		if (list) {
			fprintf (output, "%s.param type %s\n", indent, mono_metadata_string_heap (m, cols [MONO_GENERICPARAM_NAME]));
			dump_cattrs_list (list, indent);
		}

		if (++i > tdef->rows)
			break;
		mono_metadata_decode_row (tdef, i - 1, cols, MONO_GENERICPARAM_SIZE);
	} while (cols [MONO_GENERICPARAM_OWNER] == owner);
}
