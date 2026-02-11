popup_help_dialog_typed(const char *item, enum help_page_type htype)
{
  if(!help_dialog_shell) {
    create_help_dialog();
    gtk_set_relative_position(toplevel, help_dialog_shell, 10, 10);
  }
  gtk_window_present(GTK_WINDOW(help_dialog_shell));

  select_help_item_string(item, htype);
}
