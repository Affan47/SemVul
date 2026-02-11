op_v1_remove_all_identities (GkdSshAgentCall *call)
{
	GckBuilder builder = GCK_BUILDER_INIT;
	GckSession *session;
	GList *objects, *l;
	GError *error = NULL;
	GckAttributes *attrs;


	session = gkd_ssh_agent_checkout_main_session ();
	g_return_val_if_fail (session, FALSE);


	gck_builder_add_ulong (&builder, CKA_CLASS, CKO_PUBLIC_KEY);
	gck_builder_add_boolean (&builder, CKA_TOKEN, FALSE);
	gck_builder_add_string (&builder, CKA_LABEL, V1_LABEL);
	attrs = gck_attributes_ref_sink (gck_builder_end (&builder));

	objects = gck_session_find_objects (session, attrs, NULL, &error);
	gck_attributes_unref (attrs);

	if (error) {
		g_warning ("couldn't search for keys to remove: %s", egg_error_message (error));
		g_clear_error (&error);

	} else {
		for (l = objects; l; l = g_list_next (l))
			remove_by_public_key (session, l->data, FALSE);
		gck_list_unref_free (objects);
	}

	gkd_ssh_agent_checkin_main_session (session);

	egg_buffer_add_byte (call->resp, GKD_SSH_RES_SUCCESS);
	return TRUE;
}
