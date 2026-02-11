state_find (GckEnumeratorState *args,
            gboolean forward)
{
	CK_OBJECT_HANDLE objects[128];
	CK_SESSION_HANDLE session;
	CK_ATTRIBUTE_PTR attrs;
	CK_ULONG n_attrs, i,count;
	GckEnumeratorResult *result;
	CK_RV rv;


	if (!forward)
		return state_session;


	g_assert (args->session != NULL);
	g_assert (args->want_objects > 0);
	g_assert (args->funcs != NULL);

	if (!args->found)
		args->found = g_queue_new ();

	if (args->match->attributes) {
		attrs = _gck_attributes_commit_out (args->match->attributes, &n_attrs);
		if (_gck_debugging) {
			gchar *string = gck_attributes_to_string (args->match->attributes);
			_gck_debug ("finding objects matching: %s", string);
			g_free (string);
		}
	} else {
		attrs = NULL;
		n_attrs = 0;
		_gck_debug ("finding all objects");
	}

	session = gck_session_get_handle (args->session);
	g_return_val_if_fail (session, NULL);


	rv = (args->funcs->C_FindObjectsInit) (session, attrs, n_attrs);

	if (rv == CKR_OK) {
		for(;;) {
			rv = (args->funcs->C_FindObjects) (session, objects, G_N_ELEMENTS (objects), &count);
			if (rv != CKR_OK || count == 0)
				break;

			_gck_debug ("matched %lu objects", count);

			for (i = 0; i < count; i++) {
				result = g_slice_new0 (GckEnumeratorResult);
				result->handle = objects[i];
				result->session = g_object_ref (args->session);
				g_queue_push_tail (args->found, result);
			}
		}

		(args->funcs->C_FindObjectsFinal) (session);
	}

	_gck_debug ("finding objects completed with: %s", _gck_stringize_rv (rv));
	return state_results;
}
