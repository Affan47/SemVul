gftp_parse_ls_nt (char *str, gftp_file * fle)
{
  char *startpos;

  startpos = str;
  fle->datetime = parse_time (startpos, &startpos);

  fle->user = g_strdup (_("unknown"));
  fle->group = g_strdup (_("unknown"));

  startpos = goto_next_token (startpos);

  if (startpos[0] == '<')
    fle->st_mode = S_IFDIR | S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;
  else
    {
      fle->st_mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
      fle->size = gftp_parse_file_size (startpos);
    }

  startpos = goto_next_token (startpos);
  fle->file = g_strdup (startpos);
  return (0);
}
