seen_file (Hash_table const *ht, char const *file,
	   struct stat const *stats)
{
  struct F_triple new_ent;

  if (ht == NULL)
    return false;

  new_ent.name = (char *) file;
  new_ent.st_ino = stats->st_ino;
  new_ent.st_dev = stats->st_dev;

  return !!hash_lookup (ht, &new_ent);
}
