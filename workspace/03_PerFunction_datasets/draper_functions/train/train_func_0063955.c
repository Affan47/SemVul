e_shelf_move(E_Shelf *es, int x, int y)
{
   E_OBJECT_CHECK(es);
   E_OBJECT_TYPE_CHECK(es, E_SHELF_TYPE);
   es->x = x;
   es->y = y;
   if (es->popup)
     e_popup_move(es->popup, es->x, es->y);
   else
     {
        evas_object_move(es->o_event, es->zone->x + es->x, es->zone->y + es->y);
        evas_object_move(es->o_base, es->zone->x + es->x, es->zone->y + es->y);
     }
}
