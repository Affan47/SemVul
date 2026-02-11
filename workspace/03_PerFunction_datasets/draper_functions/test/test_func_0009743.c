pk_client_state_finish (PkClientState *state, const GError *error)
{
	gboolean ret;
	GError *error_local = NULL;


	ret = pk_progress_set_status (state->progress, PK_STATUS_ENUM_FINISHED);
	if (ret && state->progress_callback != NULL) {
		state->progress_callback (state->progress,
					  PK_PROGRESS_TYPE_STATUS,
					  state->progress_user_data);
	}

	if (state->cancellable_id > 0) {
		g_cancellable_disconnect (state->cancellable_client,
					  state->cancellable_id);
	}
	if (state->cancellable != NULL)
		g_object_unref (state->cancellable);

	if (state->proxy != NULL) {
		g_signal_handlers_disconnect_by_func (state->proxy,
						      G_CALLBACK (pk_client_properties_changed_cb),
						      state);
		g_signal_handlers_disconnect_by_func (state->proxy,
						      G_CALLBACK (pk_client_signal_cb),
						      state);
		g_object_unref (G_OBJECT (state->proxy));
	}

	if (state->proxy_props != NULL)
		g_object_unref (G_OBJECT (state->proxy_props));

	if (state->ret) {
		g_simple_async_result_set_op_res_gpointer (state->res,
							   g_object_ref (state->results),
							   g_object_unref);
	} else {
		g_simple_async_result_set_from_error (state->res, error);
	}


	if (state->client_helper != NULL) {
		ret = pk_client_helper_stop (state->client_helper, &error_local);
		if (!ret) {
			g_warning ("failed to stop the client helper: %s", error_local->message);
			g_error_free (error_local);
		}
		g_object_unref (state->client_helper);
	}


	pk_client_state_remove (state->client, state);


	g_simple_async_result_complete_in_idle (state->res);


	g_free (state->directory);
	g_free (state->eula_id);
	g_free (state->key_id);
	g_free (state->package_id);
	g_free (state->parameter);
	g_free (state->repo_id);
	g_strfreev (state->search);
	g_free (state->value);
	g_free (state->tid);
	g_free (state->distro_id);
	g_free (state->transaction_id);
	g_strfreev (state->files);
	g_strfreev (state->package_ids);

	if (state->results != NULL)
		g_object_unref (state->results);
	g_object_unref (state->progress);
	g_object_unref (state->res);
	g_object_unref (state->client);
	g_slice_free (PkClientState, state);
}
