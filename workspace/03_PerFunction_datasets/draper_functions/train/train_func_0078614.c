get_file_langdir (const input_file *inpf)
{


  int lang_index;
  const char *srcdir_relative_path = get_file_srcdir_relative_path (inpf);
  const char *r;

  if (!srcdir_relative_path)
    return NULL;

  lang_index = get_prefix_langdir_index (srcdir_relative_path);
  if (lang_index < 0 && strncmp (srcdir_relative_path, "c-family", 8) == 0)
    r = "c-family";
  else if (lang_index >= 0)
    r = lang_dir_names[lang_index];
  else
    r = NULL;

  return r;
}
