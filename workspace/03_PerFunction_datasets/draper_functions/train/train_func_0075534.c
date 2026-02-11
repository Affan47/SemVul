rsrc_attach_chain (rsrc_dir_chain * achain, rsrc_dir_chain * bchain)
{
  if (bchain->num_entries == 0)
    return;

  achain->num_entries += bchain->num_entries;

  if (achain->first_entry == NULL)
    {
      achain->first_entry = bchain->first_entry;
      achain->last_entry  = bchain->last_entry;
    }
  else
    {
      achain->last_entry->next_entry = bchain->first_entry;
      achain->last_entry = bchain->last_entry;
    }

  bchain->num_entries = 0;
  bchain->first_entry = bchain->last_entry = NULL;
}
