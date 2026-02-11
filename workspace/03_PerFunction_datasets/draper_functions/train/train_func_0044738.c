get_theme_index_from_id (const gchar *category_id)
{
  guint i;

  for (i=0; i<root_dir[ROOT_DIR_POPULARS_INDEX].count; i++) {
    if (g_strrstr (category_id, themes_dir[i].id)) {
      return i;
    }
  }
  g_assert_not_reached ();
}
