evas_object_polygon_is_inside(Evas_Object *obj, Evas_Coord x, Evas_Coord y)
{
   Evas_Object_Polygon *o;
   int num_edges = 0;
   Eina_List *itr;
   Evas_Polygon_Point *p;

   o = (Evas_Object_Polygon *)(obj->object_data);
   if (!o) return 0;
   if (!o->points) return 0;


   x -= o->offset.x;
   y -= o->offset.y;

   if (eina_list_count(o->points) == 1)
     {
        p = eina_list_data_get(o->points);
        return ((p->x == x) && (p->y == y));
     }

   EINA_LIST_FOREACH(o->points, itr, p)
     {
        Evas_Coord line_y;
        Eina_List *next = eina_list_next(itr);
        Evas_Polygon_Point *p_next;

        if (next)
          {
             p_next = eina_list_data_get(next);
          }
        else
          {
             p_next = eina_list_data_get(o->points);
          }


        if (((p->x < p_next->x) && (p->x <= x) && (x < p_next->x)) ||
              ((p->x > p_next->x) && (p_next->x < x) && (x <= p->x)))
          {
             line_y = ((double) (p->y - p_next->y) /
                   (double) (p->x - p_next->x)) *
                (x - p_next->x) + p_next->y;

             if (line_y < y)
                num_edges++;
          }
     }


   return ((num_edges % 2) == 1);
}
