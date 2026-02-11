hol_set_group (struct hol *hol, const char *name, int group)
{
  struct hol_entry *entry = hol_find_entry (hol, name);
  if (entry)
    entry->group = group;
}
