fill_item_list(List<Item> *item_list) const
{


  for (Field **ptr= field; *ptr; ptr++)
  {
    Item_field *item= new Item_field(*ptr);
    if (!item || item_list->push_back(item))
      return TRUE;
  }
  return FALSE;
}
