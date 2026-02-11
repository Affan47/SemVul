main(int argc, char **argv)
{
  glibtop_mountlist buf;

  glibtop_init();

  printf("%-30s %10s %10s %10s %5s %10s %10s\n",
	 "Filesystem", "Size", "Used", "Avail", "Use%", "Read", "Write");

  if (argc > 1) {
    while (*++argv)
      print_fsusage(*argv);
  } else {
    glibtop_mountentry *entries;
    size_t i;

    entries = glibtop_get_mountlist(&buf, TRUE);

    for(i = 0; i < buf.number; ++i)
      {
	print_fsusage(entries[i].mountdir);
      }

    g_free(entries);
  }

  glibtop_close();

  return 0;
}
