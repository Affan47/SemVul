e_ilist_nth_geometry_get(Evas_Object *obj, int n, Evas_Coord *x, Evas_Coord *y, Evas_Coord *w, Evas_Coord *h)
{
   E_Ilist_Item *si = NULL;

   API_ENTRY return;
   if (!sd->items) return;
   if (!(si = eina_list_nth(sd->items, n))) return;
   evas_object_geometry_get(si->o_base, x, y, w, h);
   *x -= sd->x;
   *y -= sd->y;
}
