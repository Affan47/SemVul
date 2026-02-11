combo_vars_flush (void)
{
  if (list_macros)
	gtk_combo_set_popdown_strings (GTK_COMBO (combo_macros),
								   list_macros);
  if (list_variables)
	gtk_combo_set_popdown_strings (GTK_COMBO (combo_variables),
								   list_variables);
  if (list_labels)
	gtk_combo_set_popdown_strings (GTK_COMBO (combo_labels),
								   list_labels);
}
