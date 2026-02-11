exclude_section_from_property_tables (segT sec)
{
  flagword flags = bfd_get_section_flags (stdoutput, sec);


  if ((flags & SEC_DEBUGGING)
      || !(flags & SEC_ALLOC)
      || (flags & SEC_MERGE))
    return TRUE;


  if (strcmp (sec->name, ".eh_frame") == 0)
    return TRUE;

  return FALSE;
}
