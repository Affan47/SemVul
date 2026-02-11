visu_ui_dump_dialog_getWidth(VisuUiDumpDialog *dialog)
{
  g_return_val_if_fail(dialog, 0);
  return (gint)gtk_spin_button_get_value(GTK_SPIN_BUTTON(dialog->spinWidth));
}
