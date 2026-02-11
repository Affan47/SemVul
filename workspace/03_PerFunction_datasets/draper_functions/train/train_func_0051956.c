get_exec(void) const {

  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(exec_button_p))) {
    return std::string("Yes");
  }
  return std::string("No");
}
