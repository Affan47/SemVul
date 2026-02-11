send_signals(void) {

  fax_name_sig(fax_name);
  fax_number_sig(gtk_entry_get_text(GTK_ENTRY(number_entry_p)));
  sendfax_sig();
}
