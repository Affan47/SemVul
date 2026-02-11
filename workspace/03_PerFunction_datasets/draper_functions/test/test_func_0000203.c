xlate_offset_with_removed_text (const xlate_map_t *map,
				text_action_list *action_list,
				bfd_vma offset)
{
  void *r;
  xlate_map_entry_t *e;

  if (map == NULL)
    return offset_with_removed_text (action_list, offset);

  if (map->entry_count == 0)
    return offset;

  r = bsearch (&offset, map->entry, map->entry_count,
	       sizeof (xlate_map_entry_t), &xlate_compare);
  e = (xlate_map_entry_t *) r;

  BFD_ASSERT (e != NULL);
  if (e == NULL)
    return offset;
  return e->new_address - e->orig_address + offset;
}
