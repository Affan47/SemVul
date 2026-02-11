navi_sel_ctrl(gint32 framenr)
{
  SelectedRange *range_item;

  range_item = navi_findframe_in_sel_range(framenr);
  if(range_item)
  {

     if((range_item->from == framenr)
     && (range_item->to == framenr))
     {

       navi_drop_sel_range_elem(range_item);
     }
     else if (range_item->from == framenr)
     {

       range_item->from++;
     }
     else if (range_item->to == framenr)
     {

       range_item->to--;
     }
     else
     {
       gint32 old_framenr_to;

       if(gap_debug) printf(" ** SPLIT from:%d to:%d framenr:%d\n", (int)range_item->from, (int)range_item->to, (int)framenr);


       old_framenr_to = range_item->to;
       range_item->to = framenr - 1;
       navi_add_sel_range_list(framenr +1, old_framenr_to);
     }
  }
  else
  {

     navi_add_sel_range_list(framenr, framenr);
  }

  naviD->prev_selected_framnr = framenr;

}
