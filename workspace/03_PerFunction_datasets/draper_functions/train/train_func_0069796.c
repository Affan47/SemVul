stash_find_line_fast (struct dwarf2_debug *stash,
		      asymbol *sym,
		      bfd_vma addr,
		      const char **filename_ptr,
		      unsigned int *linenumber_ptr)
{
  BFD_ASSERT (stash->info_hash_status == STASH_INFO_HASH_ON);

  if (sym->flags & BSF_FUNCTION)
    return info_hash_lookup_funcinfo (stash->funcinfo_hash_table, sym, addr,
				      filename_ptr, linenumber_ptr);
  return info_hash_lookup_varinfo (stash->varinfo_hash_table, sym, addr,
				   filename_ptr, linenumber_ptr);
}
