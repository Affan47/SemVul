shadeComboBoxGet_selectedPixbuf(VisuUiShadeCombobox *shadeComboBox)
{
  gboolean validIter;
  GtkTreeIter iter;
  GdkPixbuf *pixbuf;
  GObjectClass *klass;

  g_return_val_if_fail(VISU_UI_IS_SHADE_COMBOBOX(shadeComboBox), (GdkPixbuf*)0);

  validIter = gtk_combo_box_get_active_iter(GTK_COMBO_BOX(shadeComboBox), &iter);
  if (!validIter)
    return (GdkPixbuf*)0;

  pixbuf = (GdkPixbuf*)0;
  klass = G_OBJECT_GET_CLASS(shadeComboBox);
  gtk_tree_model_get(GTK_TREE_MODEL(VISU_UI_SHADE_COMBOBOX_CLASS(klass)->listStoredToolShades), &iter,
		     COLUMN_SHADE_PIXBUF, &pixbuf,
		     -1);
  return pixbuf;
}
