_GD_AsciiClose(struct _gd_raw_file* file)
{
  int ret;

  dtrace("%p", file);

  ret = fclose((FILE *)file->edata);
  if (ret != EOF) {
    file->fp = -1;
    dreturn("%i", 0);
    return 0;
  }

  dreturn("%i", 1);
  return 1;
}
