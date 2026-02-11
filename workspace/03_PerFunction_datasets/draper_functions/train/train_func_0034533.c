straighten (GSList *list)
{
  AnnotatePoint *inp_point = NULL;
  AnnotatePoint *first_point =  NULL;
  AnnotatePoint *last_point = NULL;
  AnnotatePoint *last_out_point =  NULL;
  gdouble degree_threshold = 15;
  GSList *list_out = NULL;
  guint lenght = 0;
  guint i;
  gdouble direction;

  lenght = g_slist_length (list);


  inp_point = (AnnotatePoint *) g_slist_nth_data (list, 0);
  first_point =  allocate_point (inp_point->x, inp_point->y, inp_point->width, inp_point->pressure);
  list_out = g_slist_prepend (list_out, first_point);

  for (i=0; i<lenght-2; i++)
    {
      AnnotatePoint *point_a = (AnnotatePoint *) g_slist_nth_data (list, i);
      AnnotatePoint *point_b = (AnnotatePoint *) g_slist_nth_data (list, i+1);
      AnnotatePoint *point_c = (AnnotatePoint *) g_slist_nth_data (list, i+2);
      gdouble direction_ab = calculate_edge_degree (point_a, point_b);
      gdouble direction_bc = calculate_edge_degree (point_b, point_c);
      gdouble delta_degree = fabs (direction_ab-direction_bc);

      if (delta_degree > degree_threshold)
        {

          AnnotatePoint *point =  allocate_point (point_b->x,
                                                  point_b->y,
                                                  point_b->width,point_b->pressure);

          list_out = g_slist_prepend (list_out, point);
        }


    }


  last_point = (AnnotatePoint *) g_slist_nth_data (list, lenght-1);
  last_out_point =  allocate_point (last_point->x,
                                    last_point->y,
                                    last_point->width,
                                    last_point->pressure);

  list_out = g_slist_prepend (list_out, last_out_point);


  list_out = g_slist_reverse (list_out);

  lenght = g_slist_length (list_out);

  if (lenght!=2)
    {
      return list_out;
    }


  direction = calculate_edge_degree (first_point, last_point);


  if ( (0-degree_threshold<=direction) && (direction<=0+degree_threshold) )
    {

      gdouble y = (first_point->y+last_point->y)/2;

      g_slist_foreach (list_out, (GFunc) point_put_y, &y);
    }


  if ( (90-degree_threshold<=direction)&& (direction<=90+degree_threshold))
    {

      gdouble x = (first_point->x+last_point->x)/2;

      g_slist_foreach (list_out, (GFunc) point_put_x, &x);
    }

  return list_out;
}
