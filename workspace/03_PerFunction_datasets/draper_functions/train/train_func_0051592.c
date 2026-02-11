on_main_but_to_hex_clicked (GtkButton * button, gpointer user_data)
{
  GtkWidget *hex_entry, *dec_entry;
  GString *hex;
  gint dec;

  hex_entry = lookup_widget (app->window_main, "main_entry_hex");
  g_assert (hex_entry);
  dec_entry = lookup_widget (app->window_main, "main_entry_dec");
  g_assert (dec_entry);

  asm_util_parse_number ((gchar *)
						 gtk_entry_get_text (GTK_ENTRY (dec_entry)),
						 &dec);
  hex = conv_dec_to_hex (dec);

  gtk_entry_set_text (GTK_ENTRY (hex_entry), hex->str);
  g_string_free (hex, TRUE);

}
