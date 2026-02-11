load_rsa_attributes (GckObject *object,
                     GckBuilder *builder,
                     GCancellable *cancellable,
                     GError **lerror)
{
	gulong attr_types[] = { CKA_MODULUS, CKA_PUBLIC_EXPONENT };
	GckAttributes *attrs;
	GError *error = NULL;

	if (check_rsa_attributes (builder)) {
		_gcr_debug ("rsa attributes already loaded");
		return TRUE;
	}

	attrs = gck_object_cache_lookup (object, attr_types, G_N_ELEMENTS (attr_types),
	                                 cancellable, &error);
	if (error != NULL) {
		_gcr_debug ("couldn't load rsa attributes: %s", error->message);
		g_propagate_error (lerror, error);
		return FALSE;
	}

	gck_builder_set_all (builder, attrs);
	gck_attributes_unref (attrs);

	return check_rsa_attributes (builder);
}
