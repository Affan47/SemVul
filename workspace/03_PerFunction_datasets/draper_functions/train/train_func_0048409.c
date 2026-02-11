objects_foreach_item (GkdSecretObjects *self,
                      GList *items,
                      const gchar *base,
                      GkdSecretObjectsForeach callback,
                      gpointer user_data)
{
	gchar *path;
	GList *l;

	for (l = items; l; l = g_list_next (l)) {
		path = object_path_for_item (base, l->data);
		(callback) (self, path, l->data, user_data);
		g_free (path);
	}
}
