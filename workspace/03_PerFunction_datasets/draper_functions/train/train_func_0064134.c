gli_stream_open_file(frefid_t fref, glui32 fmode,
    glui32 rock, int unicode)
{
  char modestr[16];
  char msg[256];
  stream_t *str;
  FILE *fl;

  if (!fref)
  {
    gli_strict_warning("stream_open_file: invalid fileref id");
    return 0;
  }


  if (fmode == filemode_ReadWrite || fmode == filemode_WriteAppend)
  {
    fl = fopen(fref->filename, "ab");
    if (!fl)
    {
      sprintf(msg, "stream_open_file: unable to open file (ab): %s", fref->filename);
      gli_strict_warning(msg);
      return 0;
    }
    fclose(fl);
  }

  switch (fmode)
  {
      case filemode_Write:
          strcpy(modestr, "w");
          break;
      case filemode_Read:
          strcpy(modestr, "r");
          break;
      case filemode_ReadWrite:
          strcpy(modestr, "r+");
          break;
      case filemode_WriteAppend:


          strcpy(modestr, "r+");
          break;
  }

  if (!fref->textmode)
    strcat(modestr, "b");

  fl = fopen(fref->filename, modestr);
  if (!fl)
  {
    sprintf(msg, "stream_open_file: unable to open file (%s): %s", modestr, fref->filename);
    gli_strict_warning(msg);
    return 0;
  }

  if (fmode == filemode_WriteAppend)
    fseek(fl, 0, 2);

  str = gli_new_stream(strtype_File,
    (fmode == filemode_Read || fmode == filemode_ReadWrite),
    !(fmode == filemode_Read),
    rock,
    unicode);
  if (!str)
  {
    gli_strict_warning("stream_open_file: unable to create stream.");
    fclose(fl);
    return 0;
  }

  str->file = fl;
  str->lastop = 0;
  str->textfile = fref->textmode;

  return str;
}
