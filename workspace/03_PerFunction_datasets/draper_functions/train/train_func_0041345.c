p_tabw_key_press_event_cb ( GtkWidget *widget
                    , GdkEvent  *event
                    , GapStbTabWidgets *tabw
                    )
{
  gint keyval;
  gboolean sensitive;
  gboolean ctrl_modifier;
  GapStbMainGlobalParams *sgpp;
  GapStoryBoard *stb;
  GdkEventKey   *kevent;

  if(gap_debug) printf("p_tabw_key_press_event_cb : tabw:%d\n", (int)tabw);

  if(tabw == NULL)
  {
    return (FALSE);
  }
  sgpp = (GapStbMainGlobalParams *)tabw->sgpp;
  stb = p_tabw_get_stb_ptr(tabw);

  ctrl_modifier = FALSE;

  switch (event->type)
  {
    case GDK_KEY_PRESS:
      kevent =  (GdkEventKey *) event;

      if(kevent->state & GDK_CONTROL_MASK)
      {
        ctrl_modifier = TRUE;
      }
      keyval = (gint)kevent->keyval;
      if(gap_debug)
      {
        printf("KEY Press : val:%d  ctrl_modifier:%d\n", (int)keyval, (int)ctrl_modifier);
      }
      switch (keyval)
      {
        case GDK_C:
        case GDK_c:
          if(ctrl_modifier)
          {
            if(gap_debug) printf("GDK_C: copy\n");
            sensitive = p_cut_copy_sensitive(stb);
            if(sensitive)
            {
              p_tabw_edit_copy_cb(NULL, tabw);
            }
            return(TRUE);
          }
          break;
        case GDK_V:
        case GDK_v:
          if(ctrl_modifier)
          {
            if(gap_debug) printf("GDK_V: paste\n");
            sensitive = p_paste_sensitive(sgpp, stb);
            if(sensitive)
            {
              p_tabw_edit_paste_cb(NULL, tabw);


              p_tabw_set_focus_to_first_fw(tabw);
            }
            return(TRUE);
          }
          break;
        case GDK_X:
        case GDK_x:
          if(ctrl_modifier)
          {
            if(gap_debug) printf("GDK_X: cut\n");
            sensitive = p_cut_copy_sensitive(stb);
            if(sensitive)
            {
              p_tabw_edit_cut_cb(NULL, tabw);
            }
            return(TRUE);
          }
          break;
        case GDK_Z:
        case GDK_z:
          if(ctrl_modifier)
          {
            if(gap_debug) printf("GDK_Z: undo\n");


            return(TRUE);
          }
          break;
      }
      break;

    default:

      break;
  }

  return FALSE;
}
