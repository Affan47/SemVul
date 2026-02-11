elaborate_diff (GtkFileChooserButton * widget, void *user_data)
{
  FileDifferences *diff = (FileDifferences *) user_data;
  char *filename;
  unsigned char *data[2];
  FILE *of;
  GString *string;
  GFileError error_type;
  signed int size[2], len, i, shared_n = 0, shared_t = 0, c;

  filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (widget));
  if (!(of = fopen (filename, "rb")))
    {
      error_type = g_file_error_from_errno (errno);
      file_error_control (error_type, RB_MODE);
      return;
    }

  fseek (of, 0, SEEK_END);
  data[0] = (unsigned char *) malloc ((size[0] = ftell (of)) * sizeof (unsigned char));
  rewind (of);
  fread (data[0], sizeof (unsigned char), size[0], of);
  fclose (of);

  data[1] = (unsigned char *) ohfa (&size[1]);
  len = (size[0] > size[1]) ? size[1] : size[0];

  string = g_string_new ("");
  for (i = 0; i < len; i++)
    {
      for (c = i; i < len && data[0][i] == data[1][i]; i++, shared_t++)
        {
          if (i == c)
            {
              g_string_append_printf (string,
                                      _("<b>%d</b>: <i>start</i> ( %8.8X ) "), ++shared_n, c + 0x10);
              c = -1;
            }
        }
      if (c == -1)
        g_string_append_printf (string, _("- <i>end</i> ( %8.8X )\n"), i + 0x10);

    }

  gtk_widget_set_sensitive (diff->expanded, TRUE);
  gtk_expander_set_label (GTK_EXPANDER (diff->expanded),
                          g_strdup_printf ("%d ( %2.1f%% )", shared_n, (float) (shared_t * 100) / len));
  gtk_label_set_markup (GTK_LABEL (diff->label), string->str);
  g_string_free (string, TRUE);
}
