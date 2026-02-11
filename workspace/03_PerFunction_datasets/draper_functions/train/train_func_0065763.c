cli_coll_rename (cli_infos_t *infos, command_context_t *ctx)
{
	gboolean retval, force;
	gchar *from_ns, *to_ns, *from_name, *to_name;
	const gchar *oldname, *newname;

	if (!command_flag_boolean_get (ctx, "force", &force)) {
		force = FALSE;
	}

	if (!command_arg_string_get (ctx, 0, &oldname)) {
		g_printf (_("Error: failed to read collection name!\n"));
		return FALSE;
	}

	if (!command_arg_string_get (ctx, 1, &newname)) {
		g_printf (_("Error: failed to read collection new name!\n"));
		return FALSE;
	}

	coll_name_split (oldname, &from_ns, &from_name);
	coll_name_split (newname, &to_ns, &to_name);

	if (strcmp (from_ns, to_ns)) {
		g_printf ("Error: collections namespaces can't be different!\n");
		retval = FALSE;
	} else {
		coll_rename (infos, oldname, newname, to_ns, force);
		retval = TRUE;
	}

	g_free (from_ns);
	g_free (from_name);
	g_free (to_ns);
	g_free (to_name);

	return retval;
}
