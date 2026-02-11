snapshot_handler(void)
{
  char *text_snapshot;
  Bit32u len;
  if (make_text_snapshot (&text_snapshot, &len) < 0) {
    BX_ERROR(("snapshot button failed, mode not implemented"));
    return;
  }

  char filename[BX_PATHNAME_LEN];
  if (BX_GUI_THIS dialog_caps & BX_GUI_DLG_SNAPSHOT) {
    int ret = SIM->ask_filename (filename, sizeof(filename),
                                 "Save snapshot as...", "snapshot.txt",
                                 bx_param_string_c::SAVE_FILE_DIALOG);
    if (ret < 0) {
      free(text_snapshot);
      return;
    }
  } else {
    strcpy (filename, "snapshot.txt");
  }
  FILE *fp = fopen(filename, "wb");
  fwrite(text_snapshot, 1, len, fp);
  fclose(fp);
  free(text_snapshot);
}
