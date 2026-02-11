bfd_elf64_archive_slurp_armap (bfd *abfd)
{
  struct artdata *ardata = bfd_ardata (abfd);
  char nextname[17];
  bfd_size_type i, parsed_size, nsymz, stringsize, carsym_size, ptrsize;
  struct areltdata *mapdata;
  bfd_byte int_buf[8];
  char *stringbase;
  bfd_byte *raw_armap = NULL;
  carsym *carsyms;
  bfd_size_type amt;

  ardata->symdefs = NULL;


  i = bfd_bread (nextname, 16, abfd);
  if (i == 0)
    return TRUE;
  if (i != 16)
    return FALSE;

  if (bfd_seek (abfd, (file_ptr) - 16, SEEK_CUR) != 0)
    return FALSE;


  if (CONST_STRNEQ (nextname, "/               "))
    return bfd_slurp_armap (abfd);

  if (! CONST_STRNEQ (nextname, "/SYM64/         "))
    {
      bfd_has_map (abfd) = FALSE;
      return TRUE;
    }

  mapdata = (struct areltdata *) _bfd_read_ar_hdr (abfd);
  if (mapdata == NULL)
    return FALSE;
  parsed_size = mapdata->parsed_size;
  bfd_release (abfd, mapdata);

  if (bfd_bread (int_buf, 8, abfd) != 8)
    {
      if (bfd_get_error () != bfd_error_system_call)
	bfd_set_error (bfd_error_malformed_archive);
      return FALSE;
    }

  nsymz = bfd_getb64 (int_buf);
  stringsize = parsed_size - 8 * nsymz - 8;

  carsym_size = nsymz * sizeof (carsym);
  ptrsize = 8 * nsymz;

  amt = carsym_size + stringsize + 1;
  ardata->symdefs = (struct carsym *) bfd_zalloc (abfd, amt);
  if (ardata->symdefs == NULL)
    return FALSE;
  carsyms = ardata->symdefs;
  stringbase = ((char *) ardata->symdefs) + carsym_size;

  raw_armap = (bfd_byte *) bfd_alloc (abfd, ptrsize);
  if (raw_armap == NULL)
    goto release_symdefs;

  if (bfd_bread (raw_armap, ptrsize, abfd) != ptrsize
      || bfd_bread (stringbase, stringsize, abfd) != stringsize)
    {
      if (bfd_get_error () != bfd_error_system_call)
	bfd_set_error (bfd_error_malformed_archive);
      goto release_raw_armap;
    }

  for (i = 0; i < nsymz; i++)
    {
      carsyms->file_offset = bfd_getb64 (raw_armap + i * 8);
      carsyms->name = stringbase;
      stringbase += strlen (stringbase) + 1;
      ++carsyms;
    }
  *stringbase = '\0';

  ardata->symdef_count = nsymz;
  ardata->first_file_filepos = bfd_tell (abfd);

  ardata->first_file_filepos += (ardata->first_file_filepos) % 2;

  bfd_has_map (abfd) = TRUE;
  bfd_release (abfd, raw_armap);

  return TRUE;

release_raw_armap:
  bfd_release (abfd, raw_armap);
release_symdefs:
  bfd_release (abfd, ardata->symdefs);
  return FALSE;
}
