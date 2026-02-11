family_combo_changed (GtkComboBox *combo,
                      GucharmapMiniFontSelection *fontsel)
{
  GtkTreeIter iter;
  char *family;

  if (!gtk_combo_box_get_active_iter (combo, &iter))
    return;

  gtk_tree_model_get (GTK_TREE_MODEL (fontsel->family_store),
                      &iter,
                      COL_FAMILIY, &family,
                      -1);
  if (!family)
    return;

  pango_font_description_set_family (fontsel->font_desc, family);
  g_free (family);

  g_object_notify (G_OBJECT (fontsel), "font-desc");
}
