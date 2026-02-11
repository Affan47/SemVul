found_min_and_max (GSList  *list,
                               gdouble *minx,
                               gdouble *miny,
                               gdouble *maxx,
                               gdouble *maxy)
{
  guint i = 0;


  AnnotatePoint *first_point = (AnnotatePoint *) g_slist_nth_data (list, i);
  *minx = first_point->x;
  *miny = first_point->y;
  *maxx = first_point->x;
  *maxy = first_point->y;

  guint lenght = g_slist_length (list);


  for (i=1; i<lenght; i++)
    {
      AnnotatePoint *cur_point = (AnnotatePoint *) g_slist_nth_data (list, i);
      *minx = MIN (*minx, cur_point->x);
      *miny = MIN (*miny, cur_point->y);
      *maxx = MAX (*maxx, cur_point->x);
      *maxy = MAX (*maxy, cur_point->y);
    }
}
