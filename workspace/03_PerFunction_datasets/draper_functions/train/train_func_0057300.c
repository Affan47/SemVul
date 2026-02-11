_gcr_subject_public_key_load (GckObject *key,
                              GCancellable *cancellable,
                              GError **error)
{
	GckBuilder builder = GCK_BUILDER_INIT;
	GckAttributes *attributes;
	GNode *asn;

	g_return_val_if_fail (GCK_IS_OBJECT (key), NULL);
	g_return_val_if_fail (cancellable == NULL || G_IS_CANCELLABLE (cancellable), NULL);
	g_return_val_if_fail (error == NULL || *error == NULL, NULL);

	lookup_attributes (key, &builder);

	if (!check_attributes (&builder)) {
		if (!load_attributes (key, &builder, cancellable, error)) {
			gck_builder_clear (&builder);
			return NULL;
		}
	}

	attributes = gck_builder_end (&builder);
	asn = _gcr_subject_public_key_for_attributes (attributes);
	if (asn == NULL) {
		g_set_error_literal (error, GCK_ERROR, CKR_TEMPLATE_INCONSISTENT,
		                     _("Couldn't build public key"));
	}

	gck_attributes_unref (attributes);
	return asn;
}
