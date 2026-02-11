perform_add_pinned_certificate (GckAttributes *search,
                                GCancellable *cancellable,
                                GError **error)
{
	GckBuilder builder = GCK_BUILDER_INIT;
	gboolean ret = FALSE;
	GError *lerr = NULL;
	GckObject *object;
	GckSession *session;
	GckSlot *slot;
	GckEnumerator *en;
	GList *slots;

	if (!gcr_pkcs11_initialize (cancellable, error))
		return FALSE;

	slots = gcr_pkcs11_get_trust_lookup_slots ();
	en = gck_slots_enumerate_objects (slots, search, CKF_RW_SESSION);
	gck_list_unref_free (slots);


	if (error && !*error)
		*error = lerr;

	object = gck_enumerator_next (en, cancellable, error);
	g_object_unref (en);

	if (*error)
		return FALSE;


	if (object) {
		g_object_unref (object);
		return TRUE;
	}

	gck_builder_add_all (&builder, search);


	slot = gcr_pkcs11_get_trust_store_slot ();
	if (slot == NULL) {
		g_set_error (error, GCK_ERROR, CKR_FUNCTION_FAILED,


		             _("Couldn't find a place to store the pinned certificate"));
		ret = FALSE;
	} else {
		session = gck_slot_open_session (slot, CKF_RW_SESSION, NULL, error);
		if (session != NULL) {
			object = gck_session_create_object (session, gck_builder_end (&builder),
			                                    cancellable, error);
			if (object != NULL) {
				g_object_unref (object);
				ret = TRUE;
			}

			g_object_unref (session);
		}

		g_object_unref (slot);
	}

	gck_builder_clear (&builder);


	g_clear_error (&lerr);

	return ret;
}
