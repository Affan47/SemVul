e_layout_child_geometry_get(Evas_Object *obj, Evas_Coord *x, Evas_Coord *y, Evas_Coord *w, Evas_Coord *h)
{
   E_Layout_Item *li;

   li = evas_object_data_get(obj, "e_layout_data");
   if (!li) return;

   if (x) *x = li->x;
   if (y) *y = li->y;
   if (w) *w = li->w;
   if (h) *h = li->h;
}
