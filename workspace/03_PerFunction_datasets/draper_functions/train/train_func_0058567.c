mov_grab_bezier_path(t_mov_gui_stuff *mgp, gint32 vectors_id, gint32 stroke_id, const char *vectorname)
{
  gint32 image_id;
  gint             num_lines;
  gint             num_points;
  gdouble          max_distance;
  gdouble          distance;
  gdouble          step_length;
  gdouble          precision;
  gint             l_ii;

  image_id = mgp->ainfo_ptr->image_id;
  step_length = 1.0;

  num_points = 1 + abs(pvals->dst_range_end - pvals->dst_range_start);
  num_points = MIN((GAP_MOV_MAX_POINT-2), num_points);
  num_lines = num_points -1;

  distance   = 0.0;
  precision = 1.0;

  if(num_lines > 0)
  {
    max_distance = gimp_vectors_stroke_get_length(vectors_id, stroke_id, precision);
    step_length = max_distance / ((gdouble)num_lines);
  }


  for(l_ii=0; l_ii < num_points ; l_ii++)
  {
    gdouble  xdouble;
    gdouble  ydouble;
    gdouble  slope;
    gboolean valid;
    gboolean success;


    success = gimp_vectors_stroke_get_point_at_dist(vectors_id
                                         , stroke_id
                                         , distance
                                         , precision
                                         , &xdouble
                                         , &ydouble
                                         , &slope
                                         , &valid
                                         );


    if(gap_debug)
    {
      printf("PATH distance: %.3f, (%.4f / %.4f) X:%03d Y: %03d slope:%.3f valid:%d success:%d\n"
            , (float)distance
            , (float)xdouble
            , (float)ydouble
            , (int)pvals->point[l_ii].p_x
            , (int)pvals->point[l_ii].p_y
            , (float)slope
            , (int)valid
            , (int)success
            );
    }

    if((!valid) || (!success))
    {


       return;
    }
    pvals->point_idx_max = l_ii;
    p_clear_one_point(l_ii);
    pvals->point[l_ii].p_x = rint(xdouble);
    pvals->point[l_ii].p_y = rint(ydouble);

    distance += step_length;
  }

}
