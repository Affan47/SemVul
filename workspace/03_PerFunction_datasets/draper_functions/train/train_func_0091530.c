navi_sel_shift(gint32 framenr)
{
  navi_drop_sel_range_list2();


  naviD->prev_selected_framnr = MAX(naviD->prev_selected_framnr
                                   ,naviD->ainfo_ptr->first_frame_nr);


  navi_add_sel_range_list(MIN(framenr, naviD->prev_selected_framnr)
                         ,MAX(framenr, naviD->prev_selected_framnr));
}
