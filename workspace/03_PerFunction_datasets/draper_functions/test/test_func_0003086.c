find_debug_info (bfd *abfd, const struct dwarf_debug_section *debug_sections,
                 asection *after_sec)
{
  asection *msec;
  const char *look;

  if (after_sec == NULL)
    {
      look = debug_sections[debug_info].uncompressed_name;
      msec = bfd_get_section_by_name (abfd, look);
      if (msec != NULL)
	return msec;

      look = debug_sections[debug_info].compressed_name;
      if (look != NULL)
	{
	  msec = bfd_get_section_by_name (abfd, look);
	  if (msec != NULL)
	    return msec;
	}

      for (msec = abfd->sections; msec != NULL; msec = msec->next)
	if (CONST_STRNEQ (msec->name, GNU_LINKONCE_INFO))
	  return msec;

      return NULL;
    }

  for (msec = after_sec->next; msec != NULL; msec = msec->next)
    {
      look = debug_sections[debug_info].uncompressed_name;
      if (strcmp (msec->name, look) == 0)
	return msec;

      look = debug_sections[debug_info].compressed_name;
      if (look != NULL && strcmp (msec->name, look) == 0)
	return msec;

      if (CONST_STRNEQ (msec->name, GNU_LINKONCE_INFO))
	return msec;
    }

  return NULL;
}
