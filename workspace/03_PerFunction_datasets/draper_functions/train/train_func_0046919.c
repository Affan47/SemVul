on_menu_save_activate (GtkWidget *widget,
                       gpointer   data)
{
  if (!modified)
    return;
  if (!write_dict (dict_file))
    {
      create_dialog (GTK_MESSAGE_ERROR, window_main, "Simpan Kamus",
                     "Kamus tidak dapat disimpan, periksa permisi anda.");
      return;
    }
  modified_notify (FALSE);
}
