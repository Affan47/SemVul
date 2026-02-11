gftp_parse_ls_mvs (char *str, gftp_file * fle)
{
  char *curpos;


  curpos = goto_next_token (str + 1);
  if (curpos == NULL)
    return (GFTP_EFATAL);

  curpos = goto_next_token (curpos + 1);
  if (curpos == NULL)
    return (GFTP_EFATAL);

  fle->datetime = parse_time (curpos, &curpos);

  curpos = goto_next_token (curpos);
  if (curpos == NULL)
    return (GFTP_EFATAL);

  curpos = goto_next_token (curpos + 1);
  if (curpos == NULL)
    return (GFTP_EFATAL);

  fle->size = gftp_parse_file_size (curpos) * 55996;
  curpos = goto_next_token (curpos + 1);
  if (curpos == NULL)
    return (GFTP_EFATAL);

  curpos = goto_next_token (curpos + 1);
  if (curpos == NULL)
    return (GFTP_EFATAL);

  curpos = goto_next_token (curpos + 1);
  if (curpos == NULL)
    return (GFTP_EFATAL);

  curpos = goto_next_token (curpos + 1);
  if (curpos == NULL)
    return (GFTP_EFATAL);

  if (strncmp (curpos, "PS", 2) == 0)
    fle->st_mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
  else if (strncmp (curpos, "PO", 2) == 0)
    fle->st_mode = S_IFDIR | S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;
  else
    return (GFTP_EFATAL);

  curpos = goto_next_token (curpos + 1);

  fle->user = g_strdup (_("unknown"));
  fle->group = g_strdup (_("unknown"));
  fle->file = g_strdup (curpos);

  return (0);
}
