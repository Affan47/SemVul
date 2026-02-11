ghw_read_directory (struct ghw_handler *h)
{
  unsigned char hdr[8];
  int nbr_entries;
  int i;

  if (fread (hdr, sizeof (hdr), 1, h->stream) != 1)
    return -1;

  nbr_entries = ghw_get_i32 (h, &hdr[4]);

  if (h->flag_verbose)
    printf ("Directory (%d entries):\n", nbr_entries);

  for (i = 0; i < nbr_entries; i++)
    {
      unsigned char ent[8];
      int pos;

      if (fread (ent, sizeof (ent), 1, h->stream) != 1)
	return -1;

      pos = ghw_get_i32 (h, &ent[4]);
      if (h->flag_verbose)
	printf (" %s at %d\n", ent, pos);
    }

  if (fread (hdr, 4, 1, h->stream) != 1)
    return -1;
  if (memcmp (hdr, "EOD", 4))
    return -1;
  return 0;
}
