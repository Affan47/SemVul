bfd_make_section_old_way (bfd *abfd, const char *name)
{
  asection *newsect;

  if (abfd->output_has_begun)
    {
      bfd_set_error (bfd_error_invalid_operation);
      return NULL;
    }

  if (strcmp (name, BFD_ABS_SECTION_NAME) == 0)
    newsect = bfd_abs_section_ptr;
  else if (strcmp (name, BFD_COM_SECTION_NAME) == 0)
    newsect = bfd_com_section_ptr;
  else if (strcmp (name, BFD_UND_SECTION_NAME) == 0)
    newsect = bfd_und_section_ptr;
  else if (strcmp (name, BFD_IND_SECTION_NAME) == 0)
    newsect = bfd_ind_section_ptr;
  else
    {
      struct section_hash_entry *sh;

      sh = section_hash_lookup (&abfd->section_htab, name, TRUE, FALSE);
      if (sh == NULL)
	return NULL;

      newsect = &sh->section;
      if (newsect->name != NULL)
	{

	  return newsect;
	}

      newsect->name = name;
      return bfd_section_init (abfd, newsect);
    }


  if (! BFD_SEND (abfd, _new_section_hook, (abfd, newsect)))
    return NULL;
  return newsect;
}
