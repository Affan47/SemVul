_bfd_elf_hash_symbol (struct elf_link_hash_entry *h)
{
  return !(h->forced_local
	   || h->root.type == bfd_link_hash_undefined
	   || h->root.type == bfd_link_hash_undefweak
	   || ((h->root.type == bfd_link_hash_defined
		|| h->root.type == bfd_link_hash_defweak)
	       && h->root.u.def.section->output_section == NULL));
}
