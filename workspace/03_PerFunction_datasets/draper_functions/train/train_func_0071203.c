anthy_check_user_dir(void)
{
  const char *hd;
  char *dn;
  struct stat st;
  hd = anthy_conf_get_str("HOME");
  dn = alloca(strlen(hd) + 10);
  sprintf(dn, "%s/.anthy", hd);
  if (stat(dn, &st) || !S_ISDIR(st.st_mode)) {
    int r;

    r = mkdir(dn, S_IRWXU);
    if (r == -1){
      anthy_log(0, "Failed to create profile directory\n");
      return ;
    }

    r = chmod(dn, S_IRUSR | S_IWUSR | S_IXUSR);
    if (r == -1) {
      anthy_log(0, "But failed to change permission.\n");
    }
  }
}
