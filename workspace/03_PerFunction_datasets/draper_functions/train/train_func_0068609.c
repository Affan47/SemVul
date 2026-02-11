bfd_slurp_bsd_armap_f2 (bfd *abfd)
{
  struct areltdata *mapdata;
  char nextname[17];
  unsigned int counter;
  bfd_byte *raw_armap, *rbase;
  struct artdata *ardata = bfd_ardata (abfd);
  char *stringbase;
  unsigned int stringsize;
  unsigned int left;
  bfd_size_type amt;
  carsym *set;
  int i = bfd_bread (nextname, 16, abfd);

  if (i == 0)
    return TRUE;
  if (i != 16)
    return FALSE;


  if (bfd_seek (abfd, (file_ptr) -16, SEEK_CUR) != 0)
    return FALSE;

  if (CONST_STRNEQ (nextname, "__.SYMDEF       ")
      || CONST_STRNEQ (nextname, "__.SYMDEF/      "))
    return do_slurp_bsd_armap (abfd);

  if (! CONST_STRNEQ (nextname, "/               "))
    {
      bfd_has_map (abfd) = FALSE;
      return TRUE;
    }

  mapdata = (struct areltdata *) _bfd_read_ar_hdr (abfd);
  if (mapdata == NULL)
    return FALSE;

  if (mapdata->parsed_size < HPUX_SYMDEF_COUNT_SIZE + BSD_STRING_COUNT_SIZE)
    {
    wrong_format:
      bfd_set_error (bfd_error_wrong_format);
    byebye:
      bfd_release (abfd, mapdata);
      return FALSE;
    }
  left = mapdata->parsed_size - HPUX_SYMDEF_COUNT_SIZE - BSD_STRING_COUNT_SIZE;

  amt = mapdata->parsed_size;
  raw_armap = (bfd_byte *) bfd_zalloc (abfd, amt);
  if (raw_armap == NULL)
    goto byebye;

  if (bfd_bread (raw_armap, amt, abfd) != amt)
    {
      if (bfd_get_error () != bfd_error_system_call)
	bfd_set_error (bfd_error_malformed_archive);
      goto byebye;
    }

  ardata->symdef_count = H_GET_16 (abfd, raw_armap);

  ardata->cache = 0;

  stringsize = H_GET_32 (abfd, raw_armap + HPUX_SYMDEF_COUNT_SIZE);
  if (stringsize > left)
    goto wrong_format;
  left -= stringsize;


  stringbase = ((char *) raw_armap
		+ HPUX_SYMDEF_COUNT_SIZE
		+ BSD_STRING_COUNT_SIZE);
  rbase = (bfd_byte *) stringbase + stringsize;
  amt = ardata->symdef_count * BSD_SYMDEF_SIZE;
  if (amt > left)
    goto wrong_format;

  ardata->symdefs = (struct carsym *) bfd_alloc (abfd, amt);
  if (!ardata->symdefs)
    return FALSE;

  for (counter = 0, set = ardata->symdefs;
       counter < ardata->symdef_count;
       counter++, set++, rbase += BSD_SYMDEF_SIZE)
    {
      set->name = H_GET_32 (abfd, rbase) + stringbase;
      set->file_offset = H_GET_32 (abfd, rbase + BSD_SYMDEF_OFFSET_SIZE);
    }

  ardata->first_file_filepos = bfd_tell (abfd);

  ardata->first_file_filepos += (ardata->first_file_filepos) % 2;


  bfd_has_map (abfd) = TRUE;
  return TRUE;
}
