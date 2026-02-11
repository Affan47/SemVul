delete_locales_from_archive (nlist, list)
     size_t nlist;
     char *list[];
{
  struct locarhandle ah;
  struct locarhead *head;
  struct namehashent *namehashtab;


  ah.fname = NULL;
  open_archive (&ah, false);

  head = ah.addr;
  namehashtab = (struct namehashent *) ((char *) ah.addr
					+ GET (head->namehash_offset));

  while (nlist-- > 0)
    {
      const char *locname = *list++;
      uint32_t hval;
      unsigned int idx;
      unsigned int incr;


      hval = archive_hashval (locname, strlen (locname));

      idx = hval % GET (head->namehash_size);
      incr = 1 + hval % (GET (head->namehash_size) - 2);


      while (GET (namehashtab[idx].name_offset) != 0)
	{
	  if (GET (namehashtab[idx].hashval) == hval
	      && (strcmp (locname,
			  ((char *) ah.addr
			   + GET (namehashtab[idx].name_offset)))
		  == 0))
	    {


	      SET (namehashtab[idx].locrec_offset, 0);
	      break;
	    }

	  idx += incr;
	  if (idx >= GET (head->namehash_size))
	    idx -= GET (head->namehash_size);
	}

      if (GET (namehashtab[idx].name_offset) == 0 && ! be_quiet)
	error (0, 0, _("locale \"%s\" not in archive"), locname);
    }

  close_archive (&ah);

  return 0;
}
