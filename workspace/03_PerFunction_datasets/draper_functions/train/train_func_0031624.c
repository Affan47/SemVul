ieee_read_optional_id (struct ieee_info *info, const bfd_byte **pp,
		       const char **pname, unsigned long *pnamlen,
		       bfd_boolean *ppresent)
{
  bfd_byte b;
  unsigned long len;

  if (*pp >= info->pend)
    {
      ieee_eof (info);
      return FALSE;
    }

  b = **pp;
  ++*pp;

  if (b <= 0x7f)
    len = b;
  else if ((ieee_record_enum_type) b == ieee_extension_length_1_enum)
    {
      len = **pp;
      ++*pp;
    }
  else if ((ieee_record_enum_type) b == ieee_extension_length_2_enum)
    {
      len = (**pp << 8) + (*pp)[1];
      *pp += 2;
    }
  else
    {
      if (ppresent != NULL)
	{
	  --*pp;
	  *ppresent = FALSE;
	  return TRUE;
	}
      ieee_error (info, *pp - 1, _("invalid string length"));
      return FALSE;
    }

  if ((unsigned long) (info->pend - *pp) < len)
    {
      ieee_eof (info);
      return FALSE;
    }

  *pname = (const char *) *pp;
  *pnamlen = len;
  *pp += len;

  if (ppresent != NULL)
    *ppresent = TRUE;

  return TRUE;
}
