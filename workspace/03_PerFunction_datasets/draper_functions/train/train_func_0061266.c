e_contact_name_from_string (const gchar *name_str)
{
	EContactName *name;
	ENameWestern *western;

	g_return_val_if_fail (name_str != NULL, NULL);

	name = e_contact_name_new ();
	western = e_name_western_parse (name_str);

	name->prefixes = g_strdup (western->prefix);
	name->given = g_strdup (western->first );
	name->additional = g_strdup (western->middle);
	name->family = g_strdup (western->last  );
	name->suffixes = g_strdup (western->suffix);

	e_name_western_free (western);

	return name;
}
