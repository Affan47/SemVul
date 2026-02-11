encode_klass_ref (MonoAotCompile *acfg, MonoClass *klass, guint8 *buf, guint8 **endbuf)
{
	gboolean shared = FALSE;


	if (klass->generic_class) {
		guint32 token;
		g_assert (klass->type_token);


		token = find_typespec_for_class (acfg, klass);
		if (!token)
			shared = TRUE;
	} else if ((klass->byval_arg.type == MONO_TYPE_VAR) || (klass->byval_arg.type == MONO_TYPE_MVAR)) {
		shared = TRUE;
	}

	if (shared) {
		guint offset = GPOINTER_TO_UINT (g_hash_table_lookup (acfg->klass_blob_hash, klass));
		guint8 *buf2, *p;

		if (!offset) {
			buf2 = g_malloc (1024);
			p = buf2;

			encode_klass_ref_inner (acfg, klass, p, &p);
			g_assert (p - buf2 < 1024);

			offset = add_to_blob (acfg, buf2, p - buf2);
			g_free (buf2);

			g_hash_table_insert (acfg->klass_blob_hash, klass, GUINT_TO_POINTER (offset + 1));
		} else {
			offset --;
		}

		p = buf;
		encode_value (MONO_AOT_TYPEREF_BLOB_INDEX, p, &p);
		encode_value (offset, p, &p);
		*endbuf = p;
		return;
	}

	encode_klass_ref_inner (acfg, klass, buf, endbuf);
}
