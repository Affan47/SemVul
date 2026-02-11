try_dir(const char *filename, char *dirname)
{
  int len;
  FILE *fp = NULL;


  if (ver_name == NULL) {
    len =  64 + strlen(LAM_VERSION);
    ver_name = malloc(len);
    snprintf(ver_name, len - 1, "lam-%s-helpfile", LAM_VERSION);
  }


  if (dirname != NULL) {
    if (filename != NULL && fp == NULL)
      fp = check_file(filename, dirname);
    if (fp == NULL)
      fp = check_file(nonver_name, dirname);
    if (fp == NULL)
      fp = check_file(ver_name, dirname);
  }

  return fp;
}
