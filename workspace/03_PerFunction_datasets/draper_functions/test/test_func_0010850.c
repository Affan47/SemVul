object_dialog_destroy (GtkObject * object) {

  AmitkObjectDialog * dialog;

  g_return_if_fail (object != NULL);
  g_return_if_fail (AMITK_IS_OBJECT_DIALOG (object));

  dialog = AMITK_OBJECT_DIALOG(object);

  if (dialog->object != NULL) {
    g_signal_handlers_disconnect_by_func(G_OBJECT(dialog->object), dialog_update_entries, dialog);
    g_signal_handlers_disconnect_by_func(G_OBJECT(dialog->object), dialog_update_interpolation, dialog);
    g_signal_handlers_disconnect_by_func(G_OBJECT(dialog->object), dialog_update_rendering, dialog);
    g_signal_handlers_disconnect_by_func(G_OBJECT(dialog->object), dialog_update_conversion, dialog);
    dialog->object->dialog = NULL;
    dialog->object = amitk_object_unref(dialog->object);
  }

  if (dialog->original_object != NULL) {
#if AMIDE_DEBUG
    {
      gchar * temp_string;
      temp_string = g_strdup_printf(_("Copy of %s"), AMITK_OBJECT_NAME(dialog->original_object));
      amitk_object_set_name(dialog->original_object,temp_string);
      g_free(temp_string);
    }
#endif
    dialog->original_object = amitk_object_unref(dialog->original_object);
  }

  if (dialog->duration_spins != NULL) {
    g_free(dialog->duration_spins);
    dialog->duration_spins = NULL;
  }

  if (GTK_OBJECT_CLASS (object_dialog_parent_class)->destroy)
    (* GTK_OBJECT_CLASS (object_dialog_parent_class)->destroy) (object);
}
