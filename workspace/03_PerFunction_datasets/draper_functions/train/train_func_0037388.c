attachment_store_save_context_free (SaveContext *save_context)
{
	g_object_unref (save_context->simple);


	g_warn_if_fail (save_context->attachment_list == NULL);


	g_warn_if_fail (save_context->error == NULL);

	if (save_context->destination) {
		g_object_unref (save_context->destination);
		save_context->destination = NULL;
	}

	g_free (save_context->filename_prefix);
	save_context->filename_prefix = NULL;

	if (save_context->fresh_directory) {
		g_object_unref (save_context->fresh_directory);
		save_context->fresh_directory = NULL;
	}

	if (save_context->trash_directory) {
		g_object_unref (save_context->trash_directory);
		save_context->trash_directory = NULL;
	}

	g_strfreev (save_context->uris);

	g_slice_free (SaveContext, save_context);
}
