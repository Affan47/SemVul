gkd_secret_unlock_with_secret (GckObject *collection,
                               GkdSecretSecret *master,
                               GError **error)
{
	GckBuilder builder = GCK_BUILDER_INIT;
	GckAttributes *attrs;
	GckObject *cred;
	gboolean locked;

	g_return_val_if_fail (GCK_IS_OBJECT (collection), FALSE);
	g_return_val_if_fail (master, FALSE);


	if (check_locked_collection (collection, &locked) && !locked)
		return TRUE;

	common_unlock_attributes (&builder, collection);
	gck_builder_add_boolean (&builder, CKA_GNOME_TRANSIENT, TRUE);
	gck_builder_add_boolean (&builder, CKA_TOKEN, TRUE);
	attrs = gck_attributes_ref_sink (gck_builder_end (&builder));

	cred = gkd_secret_session_create_credential (master->session, NULL,
	                                             attrs, master, error);

	gck_attributes_unref (attrs);

	if (cred != NULL)
		g_object_unref (cred);
	return (cred != NULL);
}
