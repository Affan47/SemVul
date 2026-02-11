on_dialog_output_mode_changed(GtkComboBox *const combobox) {
  int value = 0;
  g_object_get(combobox,"active",&value,NULL);
  if (value<2) gtk_combo_box_set_active(combobox,value=2);
  set_output_mode((unsigned int)value);
}
