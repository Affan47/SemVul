get_prefix_langdir_index (const char *f)
{
  size_t f_len = strlen (f);
  size_t lang_index;

  for (lang_index = 0; lang_index < num_lang_dirs; lang_index++)
    {
      const char * langdir = lang_dir_names [lang_index];
      size_t langdir_len = strlen (langdir);

      if (f_len > langdir_len
	  && IS_DIR_SEPARATOR (f[langdir_len])
	  && memcmp (f, langdir, langdir_len) == 0)
	return lang_index;
    }

  return -1;
}
