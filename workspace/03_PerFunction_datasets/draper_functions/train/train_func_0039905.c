html_window_get_setting (GtkWidget * widget, void *data)
{
  char *outfilename, *t;
  unsigned char *_data;
  gboolean chk;
  JHtmlExportPage jhep;
  JHtmlExportPageWidget *j = (JHtmlExportPageWidget *) data;
  extern JeexFileInfo *file[64];
  int len, l;

  t = (char *) gtk_entry_get_text (GTK_ENTRY (j->outfilename[1]));
  if (!t || *t == '\0')
    {
      _error (_("<big><b>Output Filename is empty!</b></big>\n"));
      return NULL;
    }
  if ((len = strlen (t)) > 5 && fthx ((unsigned char *) t + (len - 5), ".html"))
    {
      outfilename =
        g_strdup_printf ("%s/%s",
                         gtk_file_chooser_get_current_folder (GTK_FILE_CHOOSER (j->outfilename[0])), t);
    }
  else
    {
      outfilename =
        g_strdup_printf ("%s/%s.html",
                         gtk_file_chooser_get_current_folder (GTK_FILE_CHOOSER (j->outfilename[0])), t);
    }

  _data = (unsigned char *) ohfa (&len);
  jhep.num = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (j->rows_for_page));

  jhep.border.style = gtk_combo_box_get_active (GTK_COMBO_BOX (j->border_style));

  jhep.border.width = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (j->border_width));

  jhep.font_size = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (j->font_size));

  l = gtk_combo_box_get_active (GTK_COMBO_BOX (j->ascii_ext));
  jhep.ascii_ext = l ? TRUE : FALSE;

  t = (char *) gtk_entry_get_text (GTK_ENTRY (j->bg_color[1]));
  jhep.color.background = g_strdup (t);

  t = (char *) gtk_entry_get_text (GTK_ENTRY (j->b_color[1]));
  jhep.color.border = g_strdup (t);

  gtk_widget_destroy (j->window);
  g_free (j);

  if ((len / (jhep.num * 16)) > 500)
    {
      chk =
        _info (_
               ("If you press OK, after this message,\n"
                "jeex maked more 500 files!\n" "\n" "Continue?"), TRUE);
      if (chk)
        {
          logging_action (_("Exported `%s' to HTML `%s'\n"), _ncurrent (file)->name, outfilename);
          html_export (_ncurrent (file)->name, outfilename, _data, len, &jhep);
        }
    }
  else
    {
      logging_action (_("Exported `%s' to HTML `%s'\n"), _ncurrent (file)->name, outfilename);
      html_export (_ncurrent (file)->name, outfilename, _data, len, &jhep);
    }

  return NULL;
}
