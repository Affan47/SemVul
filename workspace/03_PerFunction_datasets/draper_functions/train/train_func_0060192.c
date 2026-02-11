save_faxfile(char *name, int width)
{
  time_t tp;
  char date[16];


  if (fsfile)
    return SAVE_BUSY;

  if (name) {
    strcpy(faxsavename, name);
  } else {
    time(&tp);
    strftime(date, 14, "%m.%d-%H:%M", localtime(&tp));
    sprintf(faxsavename, "%s/faxsave_%s.pgm", FAX_SAVEDIR, date);
  }
  return save_func(F_OPEN, width);
}
