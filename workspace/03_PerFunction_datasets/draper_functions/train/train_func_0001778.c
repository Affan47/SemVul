_e_smart_randr_monitor_adjacent_move(E_Smart_Data *sd, Evas_Object *obj, Evas_Object *skip)
{
   Eina_List *l = NULL;
   Evas_Object *mon;
   Eina_Rectangle o;


   e_smart_monitor_current_geometry_get(obj, &o.x, &o.y, NULL, NULL);
   e_layout_child_geometry_get(obj, NULL, NULL, &o.w, &o.h);


   EINA_LIST_FOREACH(sd->monitors, l, mon)
     {
        Eina_Rectangle m;


        if (((skip) && (mon == skip)) || (mon == obj))
          continue;


        e_smart_monitor_current_geometry_get(mon, &m.x, &m.y, NULL, NULL);
        e_layout_child_geometry_get(mon, NULL, NULL, &m.w, &m.h);


        if ((m.x == o.x) || (m.y == o.y))
          {
             if ((m.x == o.x))
               {
                  if ((m.y >= o.y))
                    {

                       e_layout_child_move(mon, m.x, (o.y + o.h));
                    }
               }
             else if ((m.y == o.y))
               {
                  if ((m.x >= o.x))
                    {

                       e_layout_child_move(mon, (o.x + o.w), m.y);
                    }
               }
          }
     }
}
