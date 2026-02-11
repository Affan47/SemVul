menu_add_items (GtkUIManager *ui, const char *const prefix,
		     const char *const label, guint merge, size_t count)
{
  char name[32];
  int i;
  for (i = 0; i < 2; ++i)
  {
    char *path = g_strdup_printf ("/ui/%s/%s", type[i], prefix);
    size_t j = count;
    while (j--)
    {
      snprintf (name, sizeof (name), "%s%zu", label, j);
      gtk_ui_manager_add_ui (ui, merge, path, name, name,
			     GTK_UI_MANAGER_MENUITEM, TRUE);
    }
    free (path);
  }
}
