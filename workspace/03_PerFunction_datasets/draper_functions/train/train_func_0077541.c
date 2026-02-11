ho_objlist_add_pixel (ho_objlist * object_list, int index, int x, int y)
{
  int x1 = (object_list->objects)[index].x;
  int x2 =
    (object_list->objects)[index].x + (object_list->objects)[index].width;
  int y1 = (object_list->objects)[index].y;
  int y2 =
    (object_list->objects)[index].y + (object_list->objects)[index].height;

  (object_list->objects)[index].weight++;
  if (x1 > x)
    x1 = x;
  if (y1 > y)
    y1 = y;
  if (x2 <= x)
    x2 = x + 1;
  if (y2 <= y)
    y2 = y + 1;

  (object_list->objects)[index].x = x1;
  (object_list->objects)[index].y = y1;
  (object_list->objects)[index].height = y2 - y1;
  (object_list->objects)[index].width = x2 - x1;

  return FALSE;
}
