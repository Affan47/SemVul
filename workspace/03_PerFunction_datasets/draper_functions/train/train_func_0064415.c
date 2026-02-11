set_values ()
{
  int n;
  char *s;

  strcpy (qsodata.call,
	  gtk_entry_get_text (GTK_ENTRY (qso_dialog.call_text)));

  s=qsodata.call;
  n=strlen(s);
  while (n) {
    *s = g_ascii_toupper (*s);
    s++;
    n--;
  }

  strcpy (qsodata.name,
	  gtk_entry_get_text (GTK_ENTRY (qso_dialog.name_text)));
  strcpy (qsodata.qth, gtk_entry_get_text (GTK_ENTRY (qso_dialog.qth_text)));
  strcpy (qsodata.rst_s,
	  gtk_entry_get_text (GTK_ENTRY (qso_dialog.rst_s_text)));
  strcpy (qsodata.rst_r,
	  gtk_entry_get_text (GTK_ENTRY (qso_dialog.rst_r_text)));
  strcpy (qsodata.notes,
	  gtk_entry_get_text (GTK_ENTRY (qso_dialog.notes_text)));
  strcpy (qsodata.freq,
	  gtk_entry_get_text (GTK_ENTRY (qso_dialog.freq_text)));
}
