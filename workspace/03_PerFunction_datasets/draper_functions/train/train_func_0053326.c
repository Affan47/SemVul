ho_objlist_get_index (ho_objlist * object_list, int index)
{
  while ((object_list->objects)[index].index != index)
    index = (object_list->objects)[index].index;

  return index;
}
