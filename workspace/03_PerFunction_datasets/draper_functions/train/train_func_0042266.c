e_layout_child_move(Evas_Object *obj, Evas_Coord x, Evas_Coord y)
{
   E_Layout_Item *li;

   li = evas_object_data_get(obj, "e_layout_data");
   if (!li) return;
   if ((li->x == x) && (li->y == y)) return;
   li->x = x;
   li->y = y;
   if (li->sd->frozen <= 0) _e_layout_smart_move_resize_item(li);
}
