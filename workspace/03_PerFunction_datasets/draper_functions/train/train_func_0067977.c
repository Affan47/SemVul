warn_if_cond_has_gi_scanner (GISourceScanner *scanner,
                             const gchar *text)
{

  if (strstr (text, "__GI_SCANNER__"))
    {
      gchar *filename = g_file_get_path (scanner->current_file);
      fprintf (stderr, "%s:%d: the __GI_SCANNER__ constant should only be used with simple #ifdef or #endif: %s",
               filename, lineno, text);
      g_free (filename);
    }
}
