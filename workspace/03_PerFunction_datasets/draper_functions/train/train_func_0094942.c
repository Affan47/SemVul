mov_pins_callback (GtkWidget *widget,
                      gpointer   data)
{
  t_mov_gui_stuff *mgp = data;
  gint l_idx;

  if(gap_debug) printf("mov_pins_callback\n");
  l_idx = pvals->point_idx_max;
  if (l_idx < GAP_MOV_MAX_POINT -2)
  {

    p_points_to_tab(mgp);
    pvals->point_idx_max++;

    for(l_idx = pvals->point_idx_max; l_idx >  pvals->point_idx; l_idx--)
    {

      p_copy_point(l_idx, l_idx-1);
    }

    pvals->point_idx++;
    p_point_refresh(mgp);
  }
}
