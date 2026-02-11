poke_existing_instance (int argc, char **argv){
  GDir *dir;
  const char *entry, *username, *tmp_path;
  char *prefix;
  guint prefix_len;
  char *cur_dir_tmp;
  char *cur_dir;
  char *to_open;

  g_return_val_if_fail (input == NULL, FALSE);

  tmp_path = g_get_tmp_dir ();
  dir = g_dir_open (tmp_path, 0, NULL);
  g_return_val_if_fail (dir != NULL, FALSE);

  username = g_get_user_name ();
  prefix = g_strdup_printf (PIPE_PREFIX, username);
  prefix_len = strlen (prefix);

  cur_dir_tmp = g_get_current_dir();
  cur_dir=NULL;
  cur_dir = g_strdup_printf("%s/", cur_dir_tmp);
  g_free(cur_dir_tmp);


  while ((entry = g_dir_read_name (dir))){
    if (g_str_has_prefix(entry, prefix)) {
      const char *pid_string;
      pid_t pid;
      char *filename;


      pid_string = entry + prefix_len;
      errno = 0;

      pid = strtol (pid_string, NULL, 10);
      filename = g_build_filename (tmp_path, entry, NULL);

      gphpedit_debug_message( DEBUG_IPC, "filename: %s\n", filename);
      if (!errno && pid > 0 && !kill (pid, 0)){
        int i;


        int fd = open (filename, O_WRONLY | O_NONBLOCK);

        if (fd == -1) {
          perror ("open");
          unlink (filename);
        } else {

          int k=write (fd, "", 1);
          for (i = 0; i < argc; ++i) {
            if (g_path_is_absolute(argv[i])){
              to_open = g_strdup ((gchar *) argv[i]);
            } else {
              GString *s_filename;
              s_filename = g_string_new(cur_dir);
              s_filename = g_string_append(s_filename, (gchar *) argv[i]);
              to_open=s_filename->str;
              g_free(s_filename);
            }
            if (to_open) {
              gphpedit_debug_message( DEBUG_IPC,"From %s to %s\n", argv[i], to_open);
              k=write (fd, to_open, strlen (to_open) + 1);
              g_free(to_open);
            }
          }
          close (fd);
          g_free (filename);
          g_dir_close (dir);
          g_free (prefix);
          return TRUE;
          }
        } else {

        unlink (filename);
        }
      g_free (filename);
    }
  }

  g_dir_close (dir);
  start_ipc ();
  g_free (prefix);
  g_free(cur_dir);
  return FALSE;
}
