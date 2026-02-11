html_help_gen_gamelist ()
{
	int i;
	static GSList *group_list = NULL;
	gchar *group;
	FILE *fout;
	fout = fopen ("gamelist.html", "w");
	if (!fout)
	{
		fprintf (stderr, "couldn't open gamelist.html for writing: ");
		perror (NULL);
		exit (1);
	}
	for (i=0; i<num_games; i++)
	{
		if (!games[i]->group) games[i]->group = "";
		if (!g_slist_find (group_list, games[i]->group))
			group_list = g_slist_append (group_list, games[i]->group);
	}

	fprintf (fout, "<h2> Games </h2> \n\n<ul>");
	while ((group = g_slist_nth_data (group_list, 0)))
	{
		if (group[0] != '\0')
			fprintf (fout, "<li> %s <ul>\n", group);
		for (i=0; i<num_games; i++)
		{
			if (strcmp (games[i]->group, group)) continue;
			fprintf (fout, "<li> <a href=\"/games/%s/\">%s</a> </li>\n", games[i]->name, games[i]->name);
		}
		if (group[0] != '\0')
			fprintf (fout, "</ul> </li>\n");

		group_list = g_slist_nth (group_list, 1);
	}
	fprintf (fout, "</ul>\n\n");
	fclose (fout);
}
