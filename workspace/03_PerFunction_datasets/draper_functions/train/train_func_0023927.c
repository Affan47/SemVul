write_config()
{
  char *fname;
  int i;
  FILE *f;

  if (!getenv("HOME"))
    return;

  if (asprintf (&fname, "%s/.gerstensaft", getenv("HOME")) == -1)
    return;

  if (!is_dir (fname, NULL))
    mkdir (fname, 0700);

  free (fname);
  if (asprintf (&fname, "%s/.gerstensaft/history", getenv("HOME")) == -1)
    return;

  if (!g_list_length (config.addrs)) {
    unlink (fname);
    return;
  }

  if ((f=fopen (fname,"w")) != NULL) {
    for (i=0;i<g_list_length (config.addrs); i++)
      fprintf (f, "Recipient %s\n", (char *)g_list_nth (config.addrs, i)->data);
    fclose (f);
  }

  free (fname);
  if (asprintf (&fname, "%s/.gerstensaft/config", getenv("HOME")) == -1)
    return;

  if ((f=fopen (fname,"w")) != NULL) {
    fprintf (f, "KeepFiles %s\n", config.keep?"true":"false");

    fprintf (f, "CloseWindow %s\n", config.closewindow?"true":"false");

    fprintf (f, "DotFiles %s\n", config.dotfiles?"true":"false");

    switch (config.protocol) {
    case PROTOCOL_AUTO:
      fprintf (f, "Protocol auto\n");
      break;
    case PROTOCOL_IPV4:
      fprintf (f, "Protocol ipv4\n");
      break;
    case PROTOCOL_IPV6:
      fprintf (f, "Protocol ipv6\n");
      break;
    }

    fclose (f);
  }

  free (fname);
}
