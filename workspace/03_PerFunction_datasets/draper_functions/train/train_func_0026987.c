cm_gdata_save_config(void)
{
  PrefFile *pfile;
  gchar *rcpath;

  debug_print("Saving GData plugin configuration...\n");

  rcpath = g_strconcat(get_rc_dir(), G_DIR_SEPARATOR_S, COMMON_RC, NULL);
  pfile = prefs_write_open(rcpath);
  g_free(rcpath);
  if (!pfile || (prefs_set_block_label(pfile, "GDataPlugin") < 0))
    return;

  if (prefs_write_param(cm_gdata_param, pfile->fp) < 0) {
    debug_print("failed!\n");
    g_warning(_("\nGData Plugin: Failed to write plugin configuration to file\n"));
    prefs_file_close_revert(pfile);
    return;
  }
  if (fprintf(pfile->fp, "\n") < 0) {
    FILE_OP_ERROR(rcpath, "fprintf");
    prefs_file_close_revert(pfile);
  }
  else
    prefs_file_close(pfile);
  debug_print("done.\n");
}
