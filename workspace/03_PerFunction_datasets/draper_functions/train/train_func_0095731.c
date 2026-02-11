p_tabw_new_clip_cb (GtkWidget *w
                     , GdkEventButton  *bevent
                     , GapStbTabWidgets *tabw)
{
  GapStoryBoard  *stb_dst;

  if (tabw == NULL) { return; }
  if (tabw->sgpp == NULL) { return; }

  stb_dst = p_tabw_get_stb_ptr(tabw);

  if(stb_dst != NULL)
  {
    if(bevent)
    {
      if(bevent->state & GDK_SHIFT_MASK)
      {
        if (stb_dst->active_section != stb_dst->mask_section)
        {
          p_tabw_add_att_elem (tabw, tabw->sgpp, stb_dst);
        }
        return;
      }
      if(bevent->state & GDK_CONTROL_MASK)
      {
        if (stb_dst->active_section == gap_story_find_main_section(stb_dst))
        {
          p_tabw_add_section_elem (tabw, tabw->sgpp, stb_dst);
        }
        return;
      }
    }

    p_tabw_add_elem (tabw, tabw->sgpp, stb_dst);

  }
}
