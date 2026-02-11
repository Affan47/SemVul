folder_rename (CamelFolder *folder,
               const gchar *new)
{
	gchar *tmp;

	d (printf ("CamelFolder:rename ('%s')\n", new));

	camel_folder_set_full_name (folder, new);

	tmp = strrchr (new, '/');
	camel_folder_set_display_name (folder, (tmp != NULL) ? tmp + 1 : new);
}
