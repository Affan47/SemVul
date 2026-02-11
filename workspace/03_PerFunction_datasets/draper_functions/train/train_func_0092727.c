double_linked_list_exclude(Query_cache_block *point,
					Query_cache_block **list_pointer)
{
  DBUG_ENTER("Query_cache::double_linked_list_exclude");
  DBUG_PRINT("qcache", ("excluding block 0x%lx, list 0x%lx",
		      (ulong) point, (ulong) list_pointer));
  if (point->next == point)
    *list_pointer = 0;
  else
  {
    point->next->prev = point->prev;
    point->prev->next = point->next;


    if (point == *list_pointer)
      *list_pointer= point->next;
  }
  DBUG_VOID_RETURN;
}
