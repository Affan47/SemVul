cleanup_items(Item *item)
{
  DBUG_ENTER("cleanup_items");
  for (; item ; item=item->next)
    item->cleanup();
  DBUG_VOID_RETURN;
}
