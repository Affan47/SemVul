find_key (GckSession *session, CK_ATTRIBUTE_TYPE method, CK_MECHANISM_TYPE mech)
{
	GckBuilder builder = GCK_BUILDER_INIT;
	GList *objects, *l;
	GckObject *object = NULL;
	CK_MECHANISM_TYPE_PTR mechs;
	gboolean match;
	gsize n_mechs;

	gck_builder_add_boolean (&builder, method, TRUE);
	objects = gck_session_find_objects (session, gck_builder_end (&builder), NULL, NULL);
	g_assert (objects);

	for (l = objects; l; l = g_list_next (l)) {
		if (mech) {
			mechs = (gulong *)gck_object_get_data (l->data, CKA_ALLOWED_MECHANISMS,
			                                       NULL, &n_mechs, NULL);
			g_assert (mechs);
			g_assert (n_mechs == sizeof (CK_MECHANISM_TYPE));


			match = (*mechs != mech);
			g_free (mechs);

			if (match)
				continue;
		}
		object = l->data;
		g_object_ref (object);
		break;
	}

	gck_list_unref_free (objects);
	return object;
}
