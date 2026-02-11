linux_link_hash_newfunc (struct bfd_hash_entry *entry,
			 struct bfd_hash_table *table,
			 const char *string)
{
  struct linux_link_hash_entry *ret = (struct linux_link_hash_entry *) entry;


  if (ret == (struct linux_link_hash_entry *) NULL)
    ret = ((struct linux_link_hash_entry *)
	   bfd_hash_allocate (table, sizeof (struct linux_link_hash_entry)));
  if (ret == NULL)
    return (struct bfd_hash_entry *) ret;


  ret = ((struct linux_link_hash_entry *)
	 NAME(aout,link_hash_newfunc) ((struct bfd_hash_entry *) ret,
				       table, string));
  if (ret != NULL)
    {

    }

  return (struct bfd_hash_entry *) ret;
}
