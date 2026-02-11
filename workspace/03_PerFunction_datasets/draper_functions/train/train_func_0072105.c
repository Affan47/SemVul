elf64_ia64_hash_table_create (bfd *abfd)
{
  struct elf64_ia64_link_hash_table *ret;

  ret = bfd_zmalloc ((bfd_size_type) sizeof (*ret));
  if (!ret)
    return NULL;

  if (!_bfd_elf_link_hash_table_init (&ret->root, abfd,
				      elf64_ia64_new_elf_hash_entry,
				      sizeof (struct elf64_ia64_link_hash_entry),
				      IA64_ELF_DATA))
    {
      free (ret);
      return NULL;
    }

  ret->loc_hash_table = htab_try_create (1024, elf64_ia64_local_htab_hash,
					 elf64_ia64_local_htab_eq, NULL);
  ret->loc_hash_memory = objalloc_create ();
  if (!ret->loc_hash_table || !ret->loc_hash_memory)
    {
      free (ret);
      return NULL;
    }

  return &ret->root.root;
}
