copy_asset(const struct dirent* d) {
  u8 *itmp, *otmp, buf[1024];
  s32 i, o;

  if (d->d_name[0] == '.' || !strcmp(d->d_name, "COPYING")) return 0;

  itmp = ck_alloc(strlen(ASSETS_DIR) + strlen(d->d_name) + 2);
  sprintf((char*)itmp, "%s/%s", ASSETS_DIR, d->d_name);
  i = open((char*)itmp, O_RDONLY);

  otmp = ck_alloc(strlen((char*)ca_out_dir) + strlen(d->d_name) + 2);
  sprintf((char*)otmp, "%s/%s", ca_out_dir, d->d_name);
  o = open((char*)otmp, O_WRONLY | O_CREAT | O_EXCL, 0644);

  if (i >= 0 && o >= 0) {
    s32 c;
    while ((c = read(i, buf, 1024)) > 0)
      if (write(o, buf, c) != c) break;
  }

  close(i);
  close(o);

  ck_free(itmp);
  ck_free(otmp);

  return 0;

}
