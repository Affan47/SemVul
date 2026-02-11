fileKindChangedForSpin(GtkToggleButton *button, gpointer data)
{
  struct FileChooserSpin_struct* param = data;
  GSList *tmpLst;

  if (!gtk_toggle_button_get_active(button))
    return;

  tmpLst = gtk_file_chooser_list_filters(GTK_FILE_CHOOSER(param->fileChooserDialog));
  gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(param->fileChooserDialog),
			      (GtkFileFilter*)(tmpLst->next->data));
  param->fileKind = FILE_KIND_SPIN;

  gtk_widget_set_sensitive(param->apply[1], TRUE);
  gtk_widget_set_sensitive(param->apply[0], FALSE);

  if (param->files[1])
    gtk_file_chooser_select_filename(GTK_FILE_CHOOSER(param->fileChooserDialog),
				     param->files[1]);
}
