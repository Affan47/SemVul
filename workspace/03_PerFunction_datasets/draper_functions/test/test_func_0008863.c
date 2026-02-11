gog_theme_find_element (GogTheme const *theme, GogObject const *obj)
{
	GogThemeElement *elem = NULL;
	GObjectClass *klass = NULL;
	char const *name;

	if (theme == NULL)
		theme = default_theme;
	g_return_val_if_fail (theme != NULL, NULL);


	if (elem == NULL && obj->role != NULL && obj->parent != NULL) {
		GogThemeElement key;


		key.role_id = (char *) obj->role->id;
		key.klass_name = (char *) G_OBJECT_TYPE_NAME (obj->parent);
		elem = g_hash_table_lookup (theme->elem_hash_by_role, &key);
	}

	if (elem == NULL && obj->role != NULL) {
		GogThemeElement key;


		key.role_id = (char *) obj->role->id;
			key.klass_name = NULL;
			elem = g_hash_table_lookup (theme->elem_hash_by_role, &key);
	}


	if (elem == NULL) {
		klass = G_OBJECT_GET_CLASS (obj);
		do {
			name = G_OBJECT_CLASS_NAME (klass);

			elem = g_hash_table_lookup (
				theme->elem_hash_by_class, name);
			if (elem == NULL) {
				name = g_hash_table_lookup (
					theme->class_aliases, name);
				if (name != NULL)
					elem = g_hash_table_lookup (
						theme->elem_hash_by_class, name);
			}
			if (elem == NULL &&
			    global_class_aliases != NULL) {
				name = g_hash_table_lookup (
					global_class_aliases, G_OBJECT_CLASS_NAME (klass));
				if (name != NULL)
					elem = g_hash_table_lookup (
						theme->elem_hash_by_class, name);
			}
		} while (elem == NULL &&
			 (klass = g_type_class_peek_parent (klass)) != NULL);
	}


	if (elem == NULL && theme != default_theme)
		elem = gog_theme_find_element (default_theme, obj);

	return elem;
}
