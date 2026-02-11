find_seek_offset_clrscr (FILE * fp)
{
  off_t raw_seek_offset = 0;
  off_t raw_seek_offset2 = 0;
  off_t seek_offset_clrscr;

  raw_seek_offset = find_last_string_in_file(fp, "\033[2J");
  raw_seek_offset2 = find_last_string_in_file(fp, "\033[H\033[J");
  if (raw_seek_offset2>raw_seek_offset) raw_seek_offset=raw_seek_offset2;

  seek_offset_clrscr = 0;

  fseek (fp, 0, SEEK_SET);
  while (1)
    {
      char *buf;
      Header h;
      long offset;

      if (ttyread (fp, &h, &buf, 0) != READ_DATA)
        {
          break;
        }

      free (buf);

      offset = ftell(fp);
      if (offset < raw_seek_offset)
          seek_offset_clrscr = ftell (fp);
      else
          break;
    }

  return seek_offset_clrscr;
}
