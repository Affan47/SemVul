and_items(Item* cond, Item *item)
{
  return (cond? (new Item_cond_and(cond, item)) : item);
}
