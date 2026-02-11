_update (GtkWidget * widget, void *data)
{
  unsigned char *ddata;
  unsigned long dlen;
  char *str, i;
  char **info;
  FILE *of;
  GtkTextIter iter, start, end;
  GtkTextMark *mark;
  GFileError error_type;
  extern JeexPreferences *preferences;
  extern JeexFileInfo *file[64];

  logging_action (_("Updating file `%s'\n"), _ncurrent (file)->name);


  if (!(of = fopen (_ncurrent (file)->name, "rb")))
    {

      error_type = g_file_error_from_errno (errno);
      file_error_control (error_type, RB_MODE);
      return NULL;
    }


  if (g_file_test (_ncurrent (file)->name, G_FILE_TEST_IS_DIR))
    {
      _error (_("<big><b>Unable to open file</b></big>\n"
                "\nThe file you are trying to open is a directory."));
      fclose (of);
      return NULL;
    }


  if (!control_size (of))
    {
      _error (g_strdup_printf
              (_("<big><b>File too large!</b></big>\n"
                 "\nFile size higher than <i>%s</i>."),
               g_format_size_for_display ((goffset) preferences->max_filesize)));
      fclose (of);
      return NULL;
    }


  gtk_text_buffer_get_bounds (_ncurrent (notebook->buffer), &start, &end);
  gtk_text_buffer_delete (_ncurrent (notebook->buffer), &start, &end);


  _ncurrent (notebook->buffer) =
    gtk_text_view_get_buffer (GTK_TEXT_VIEW (_ncurrent (notebook->textview)));
  mark = gtk_text_buffer_get_insert (_ncurrent (notebook->buffer));
  gtk_text_buffer_get_iter_at_mark (_ncurrent (notebook->buffer), &iter, mark);


  gdk_color_parse (preferences->color, &(textview->color));
  gtk_widget_modify_text (_ncurrent (notebook->textview), GTK_STATE_NORMAL, &(textview->color));


  dlen = load_exe (of, &ddata);
  info_type (FALSE, ddata, dlen);
  str = make_string (&ddata, dlen);
  fclose (of);

  gtk_text_buffer_set_text (_ncurrent (notebook->buffer), str, -1);
  g_free (str);
  free (ddata);

  info = inap (_ncurrent (file)->name);
  _ncurrent (file)->new = FALSE;
  _ncurrent (file)->modified = FALSE;


  if ((i = strlen (info[0])) > preferences->max_tabchars)
    {
      str = g_strndup (info[0], preferences->max_tabchars);
      g_free (info[0]);
      info[0] = g_strdup_printf ("%s...", str);
      g_free (str);
    }
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (notebook->notebook),
                              _ncurrent (notebook->table), gtk_label_new (info[0]));

  g_free (info[0]);
  g_free (info[1]);
  g_free (info);

  return NULL;
}
