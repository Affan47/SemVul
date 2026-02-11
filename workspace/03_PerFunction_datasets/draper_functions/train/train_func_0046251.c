get_relocs (bfd *abfd, asection *sec, void *dataarg)
{
  struct get_relocs_info *data = (struct get_relocs_info *) dataarg;

  *data->secs = sec;

  if ((sec->flags & SEC_RELOC) == 0)
    {
      *data->relocs = NULL;
      *data->relcount = 0;
    }
  else
    {
      long relsize;

      relsize = bfd_get_reloc_upper_bound (abfd, sec);
      if (relsize < 0)
	bfd_fatal (bfd_get_filename (abfd));

      *data->relocs = (arelent **) xmalloc (relsize);
      *data->relcount = bfd_canonicalize_reloc (abfd, sec, *data->relocs,
						data->syms);
      if (*data->relcount < 0)
	bfd_fatal (bfd_get_filename (abfd));
    }

  ++data->secs;
  ++data->relocs;
  ++data->relcount;
}
