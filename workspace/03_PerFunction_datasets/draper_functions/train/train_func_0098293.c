o_undo_cleanup(void)
{
  int i;
  char *filename;

  for (i = 0 ; i < undo_file_index; i++) {
    filename = g_strdup_printf("%s%cgschem.save%d_%d.sch", tmp_path,
                               G_DIR_SEPARATOR, prog_pid, i);
    unlink(filename);
    g_free(filename);
  }

  g_free(tmp_path);
  tmp_path = NULL;
}
