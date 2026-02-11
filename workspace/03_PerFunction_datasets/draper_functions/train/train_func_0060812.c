mov_prot_follow_callback (GtkWidget *widget,
                         GdkEventButton *bevent,
                         gpointer data)
{
  gdouble  l_startangle;
  int     key_modifier;

  t_mov_gui_stuff *mgp = data;
  key_modifier = 0;

  if(gap_debug) printf("mov_prot_follow_callback\n");


  key_modifier = 0;
  if (bevent->state & GDK_SHIFT_MASK)
  {
    key_modifier = 1;
  }

  if(gap_debug)
  {
    printf("key_modifier %d\n", (int)key_modifier);
  }

  if( pvals->point_idx_max > 1)
  {
    l_startangle = 0.0;
    if(key_modifier != 0)
    {

      p_points_to_tab(mgp);
      l_startangle = pvals->point[0].rotation;
    }
    gap_mov_exec_calculate_rotate_follow(pvals, l_startangle);
  }

  p_point_refresh(mgp);
  mov_set_instant_apply_request(mgp);
}
