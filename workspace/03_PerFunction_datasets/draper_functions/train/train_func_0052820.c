xbsd_write_bootstrap (void)
{
  char *bootdir = BSD_LINUX_BOOTDIR;
  char path[sizeof(BSD_LINUX_BOOTDIR) + 1 + 2 + 4];
  char *dkbasename;
  struct xbsd_disklabel dl;
  char *d, *p, *e;
  int sector;

  if (xbsd_dlabel.d_type == BSD_DTYPE_SCSI)
    dkbasename = "sd";
  else
    dkbasename = "wd";

  printf (_("Bootstrap: %sboot -> boot%s (%s): "),
	  dkbasename, dkbasename, dkbasename);
  if (read_line (NULL)) {
    line_ptr[strlen (line_ptr)-1] = '\0';
    dkbasename = line_ptr;
  }
  snprintf (path, sizeof(path), "%s/%sboot", bootdir, dkbasename);
  if (!xbsd_get_bootstrap (path, disklabelbuffer, (int) xbsd_dlabel.d_secsize))
    return;


  d = &disklabelbuffer[BSD_LABELSECTOR * SECTOR_SIZE];
  memmove (&dl, d, sizeof (struct xbsd_disklabel));


  memset (d, 0, sizeof (struct xbsd_disklabel));

  snprintf (path, sizeof(path), "%s/boot%s", bootdir, dkbasename);
  if (!xbsd_get_bootstrap (path, &disklabelbuffer[xbsd_dlabel.d_secsize],
			  (int) xbsd_dlabel.d_bbsize - xbsd_dlabel.d_secsize))
    return;

  e = d + sizeof (struct xbsd_disklabel);
  for (p=d; p < e; p++)
    if (*p) {
      fprintf (stderr, _("Bootstrap overlaps with disk label!\n"));
      exit ( EXIT_FAILURE );
    }

  memmove (d, &dl, sizeof (struct xbsd_disklabel));

#if defined (__powerpc__) || defined (__hppa__)
  sector = 0;
#elif defined (__alpha__)
  sector = 0;
  alpha_bootblock_checksum (disklabelbuffer);
#else
  sector = get_start_sect(xbsd_part);
#endif

  if (lseek (fd, (off_t) sector * SECTOR_SIZE, SEEK_SET) == -1)
    fatal (unable_to_seek);
  if (BSD_BBSIZE != write (fd, disklabelbuffer, BSD_BBSIZE))
    fatal (unable_to_write);

#if defined (__alpha__)
  printf (_("Bootstrap installed on %s.\n"), disk_device);
#else
  printf (_("Bootstrap installed on %s.\n"),
    partname (disk_device, xbsd_part_index+1, 0));
#endif

  sync_disks ();
}
