set_class(const std::string& class_string) {

  if (!class_string.compare("1")) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(class1_button_p), true);
  }
  else if (!class_string.compare("2")) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(class2_button_p), true);
  }
  else if (!class_string.compare("2.0")) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(class20_button_p), true);
  }
  else gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(auto_button_p), true);
}
