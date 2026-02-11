_bfd_stab_section_offset (asection *stabsec,
			  void * psecinfo,
			  bfd_vma offset)
{
  struct stab_section_info *secinfo;

  secinfo = (struct stab_section_info *) psecinfo;

  if (secinfo == NULL)
    return offset;

  if (offset >= stabsec->rawsize)
    return offset - stabsec->rawsize + stabsec->size;

  if (secinfo->cumulative_skips)
    {
      bfd_vma i;

      i = offset / STABSIZE;

      if (secinfo->stridxs [i] == (bfd_size_type) -1)
	return (bfd_vma) -1;

      return offset - secinfo->cumulative_skips [i];
    }

  return offset;
}
