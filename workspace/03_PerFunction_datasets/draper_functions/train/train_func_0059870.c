other_address_button_toggled_impl(void) {

  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(other_address_button_p))) {
    gtk_editable_set_editable(GTK_EDITABLE(other_addresses_entry_p), true);
    gtk_widget_set_sensitive(GTK_WIDGET(other_addresses_entry_p), true);
  }
  else {
    gtk_editable_set_editable(GTK_EDITABLE(other_addresses_entry_p), false);
    gtk_widget_set_sensitive(GTK_WIDGET(other_addresses_entry_p), false);
  }
}
