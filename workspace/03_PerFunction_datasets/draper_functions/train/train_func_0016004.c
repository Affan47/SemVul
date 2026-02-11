_bfd_elf_adjust_dynamic_symbol (struct elf_link_hash_entry *h, void *data)
{
  struct elf_info_failed *eif = (struct elf_info_failed *) data;
  bfd *dynobj;
  const struct elf_backend_data *bed;

  if (! is_elf_hash_table (eif->info->hash))
    return FALSE;


  if (h->root.type == bfd_link_hash_indirect)
    return TRUE;


  if (! _bfd_elf_fix_symbol_flags (h, eif))
    return FALSE;


  if (!h->needs_plt
      && h->type != STT_GNU_IFUNC
      && (h->def_regular
	  || !h->def_dynamic
	  || (!h->ref_regular
	      && (h->u.weakdef == NULL || h->u.weakdef->dynindx == -1))))
    {
      h->plt = elf_hash_table (eif->info)->init_plt_offset;
      return TRUE;
    }


  if (h->dynamic_adjusted)
    return TRUE;


  h->dynamic_adjusted = 1;


  if (h->u.weakdef != NULL)
    {


      h->u.weakdef->ref_regular = 1;


      if (! _bfd_elf_adjust_dynamic_symbol (h->u.weakdef, eif))
	return FALSE;
    }


  if (h->size == 0
      && h->type == STT_NOTYPE
      && !h->needs_plt)
    (*_bfd_error_handler)
      (_("warning: type and size of dynamic symbol `%s' are not defined"),
       h->root.root.string);

  dynobj = elf_hash_table (eif->info)->dynobj;
  bed = get_elf_backend_data (dynobj);

  if (! (*bed->elf_backend_adjust_dynamic_symbol) (eif->info, h))
    {
      eif->failed = TRUE;
      return FALSE;
    }

  return TRUE;
}
