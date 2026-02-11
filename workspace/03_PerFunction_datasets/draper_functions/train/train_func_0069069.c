generic_flags_write(MMAPString * mmapstr, size_t * indx,
			       struct mail_flags * flags)
{
  int r;

  r = mailimf_cache_int_write(mmapstr, indx,
      flags->fl_flags & ~MAIL_FLAG_NEW);
  if (r != MAIL_NO_ERROR)
    return r;

  r = flags_extension_write(mmapstr, indx,
      flags->fl_extension);
  if (r != MAIL_NO_ERROR)
    return r;

  return MAIL_NO_ERROR;
}
