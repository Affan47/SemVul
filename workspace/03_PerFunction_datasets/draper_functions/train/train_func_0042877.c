amitk_thresholds_dialog_new (GList * objects, GtkWindow * parent) {

  AmitkThresholdsDialog *dialog;
  GList * data_sets;

  g_return_val_if_fail(objects != NULL, NULL);


  data_sets = amitk_objects_get_of_type(objects, AMITK_OBJECT_TYPE_DATA_SET, FALSE);
  g_return_val_if_fail(data_sets != NULL, NULL);

  dialog = g_object_new(AMITK_TYPE_THRESHOLDS_DIALOG, NULL);
  thresholds_dialog_construct(dialog, parent, data_sets);
  gtk_window_set_title (GTK_WINDOW (dialog), _("Threshold Dialog"));

  gtk_window_set_transient_for(GTK_WINDOW (dialog), parent);
  gtk_window_set_destroy_with_parent(GTK_WINDOW (dialog), TRUE);
  gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);

  amitk_objects_unref(data_sets);

  return GTK_WIDGET (dialog);

}
