fpm_valid_edit_data() {
  if (glb_edit_data == NULL) {
    fpm_message(GTK_WINDOW(gui->main_window), _("\nPlease select a row."), GTK_MESSAGE_INFO);
    return(FALSE);
  }
  return(TRUE);
}
