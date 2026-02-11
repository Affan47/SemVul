copy_out_member (mapelt, archive_indesc, outdesc, outname)
     struct mapelt *mapelt;
     int archive_indesc;
     int outdesc;
     char *outname;
{
  struct ar_hdr header;
  int indesc;

  if (mapelt->info.name == 0)

    return;

  header_from_map (&header, mapelt);

  if (mapelt->info.offset != 0)
    {
      indesc = archive_indesc;
      lseek (indesc, mapelt->info.data_offset, 0);
    }
  else
    {
      indesc = open (mapelt->info.name, 0, 0);
      if (indesc < 0)
	{
	  perror_with_name (mapelt->info.name);
	  return;
	}
    }

  mywrite (outdesc, &header, sizeof (header), outname);

  if (mapelt->info.data_offset == 0)
    mapelt->info.data_offset = lseek (outdesc, 0L, 1);

  {
    char buf[BUFSIZE];
    int tocopy = mapelt->info.size;
    while (tocopy > 0)
      {
	int thistime = tocopy;
	if (thistime > BUFSIZE) thistime = BUFSIZE;
        read (indesc, buf, thistime);
	mywrite (outdesc, buf, thistime, outname);
	tocopy -= thistime;
      }
  }

  if (indesc != archive_indesc)
    close (indesc);

  if (mapelt->info.size & 1)
    mywrite (outdesc, "\n", 1, outname);
}
