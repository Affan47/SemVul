expand_initial_tilde (const char *path)
{
  char *slash_after_user_name, *user_name;
  struct passwd *passwd_file_entry;

  if (path[1] == '/' || path[1] == '\0') {
    return g_build_filename (g_get_home_dir (), &path[1], NULL);
  }

  slash_after_user_name = strchr (&path[1], '/');
  if (slash_after_user_name == NULL) {
    user_name = g_strdup (&path[1]);
  } else {
    user_name = g_strndup (&path[1],
                           slash_after_user_name - &path[1]);
  }
  passwd_file_entry = getpwnam (user_name);
  g_free (user_name);

  if (passwd_file_entry == NULL || passwd_file_entry->pw_dir == NULL) {
    return g_strdup (path);
  }

  return g_strconcat (passwd_file_entry->pw_dir,
                      slash_after_user_name,
                      NULL);
}
