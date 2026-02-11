gck_modules_initialize_registered (GCancellable *cancellable,
                                   GError **error)
{
	InitializeRegistered args = { GCK_ARGUMENTS_INIT, 0,  };

	if (!_gck_call_sync (NULL, perform_initialize_registered, NULL, &args, cancellable, error)) {
		if (args.error) {
			g_clear_error (error);
			g_propagate_error (error, args.error);
			args.error = NULL;
		}
	}

	g_clear_error (&args.error);
	return args.results;
}
