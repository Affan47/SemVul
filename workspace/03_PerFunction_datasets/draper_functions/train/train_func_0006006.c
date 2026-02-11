scan_uid(void)
{
	struct passwd	*pw;
	gchar		*old, *home, *name;

	setpwent();
	while((pw = getpwent()) != NULL)
	{
		if((old = g_hash_table_lookup(the_usr.dict_uname, GINT_TO_POINTER((gint) pw->pw_uid))) != NULL)
		{
			if((home = g_hash_table_lookup(the_usr.dict_uhome, old)) != NULL)
			{
				g_hash_table_remove(the_usr.dict_uname, GINT_TO_POINTER((gint) pw->pw_uid));
				g_hash_table_remove(the_usr.dict_uhome, old);
				g_free(old);
				g_free(home);
			}
			else
				fprintf(stderr, "USERINFO: passwd data for '%s' (%d) has no home dir!\n", old, (gint) pw->pw_uid);
		}
		if((name = g_strdup(pw->pw_name)) != NULL)
		{
			if((home = g_strdup(pw->pw_dir)) != NULL)
			{
				g_hash_table_insert(the_usr.dict_uname, GINT_TO_POINTER((gint) pw->pw_uid), name);
				g_hash_table_insert(the_usr.dict_uhome, name, home);
			}
			else
			{
				g_free(name);
				fprintf(stderr, "USERINFO: Couldn't duplicate home dir\n");
			}
		}
		else
			fprintf(stderr, "USERINFO: Couldn't duplicate user name string\n");
	}
	endpwent();
}
