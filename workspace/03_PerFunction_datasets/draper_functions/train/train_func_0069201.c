_bfd_handle_already_linked (asection *sec,
			    struct bfd_section_already_linked *l,
			    struct bfd_link_info *info)
{
  switch (sec->flags & SEC_LINK_DUPLICATES)
    {
    default:
      abort ();

    case SEC_LINK_DUPLICATES_DISCARD:


      if (info->loading_lto_outputs
	  && (l->sec->owner->flags & BFD_PLUGIN) != 0)
	{
	  l->sec = sec;
	  return FALSE;
	}
      break;

    case SEC_LINK_DUPLICATES_ONE_ONLY:
      info->callbacks->einfo
	(_("%B: ignoring duplicate section `%A'\n"),
	 sec->owner, sec);
      break;

    case SEC_LINK_DUPLICATES_SAME_SIZE:
      if ((l->sec->owner->flags & BFD_PLUGIN) != 0)
	;
      else if (sec->size != l->sec->size)
	info->callbacks->einfo
	  (_("%B: duplicate section `%A' has different size\n"),
	   sec->owner, sec);
      break;

    case SEC_LINK_DUPLICATES_SAME_CONTENTS:
      if ((l->sec->owner->flags & BFD_PLUGIN) != 0)
	;
      else if (sec->size != l->sec->size)
	info->callbacks->einfo
	  (_("%B: duplicate section `%A' has different size\n"),
	   sec->owner, sec);
      else if (sec->size != 0)
	{
	  bfd_byte *sec_contents, *l_sec_contents = NULL;

	  if (!bfd_malloc_and_get_section (sec->owner, sec, &sec_contents))
	    info->callbacks->einfo
	      (_("%B: could not read contents of section `%A'\n"),
	       sec->owner, sec);
	  else if (!bfd_malloc_and_get_section (l->sec->owner, l->sec,
						&l_sec_contents))
	    info->callbacks->einfo
	      (_("%B: could not read contents of section `%A'\n"),
	       l->sec->owner, l->sec);
	  else if (memcmp (sec_contents, l_sec_contents, sec->size) != 0)
	    info->callbacks->einfo
	      (_("%B: duplicate section `%A' has different contents\n"),
	       sec->owner, sec);

	  if (sec_contents)
	    free (sec_contents);
	  if (l_sec_contents)
	    free (l_sec_contents);
	}
      break;
    }


  sec->output_section = bfd_abs_section_ptr;
  sec->kept_section = l->sec;
  return TRUE;
}
