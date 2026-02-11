navi_add_sel_range_list(gint32 framenr_from, gint32 framenr_to)
{
  SelectedRange *range_list;
  SelectedRange *range_item;
  SelectedRange *range_prev;
  SelectedRange *range_next;

  range_prev = NULL;
  range_next = naviD->sel_range_list;
  range_list = naviD->sel_range_list;
  while(range_list)
  {
    if(framenr_from < range_list->from)
    {
      break;
    }
    range_prev = range_list;
    range_list = range_list->next;
    range_next = range_list;
  }

  range_item = g_new(SelectedRange, 1);
  range_item->from = framenr_from;
  range_item->to = framenr_to;

  if(range_prev == NULL)
  {

    range_item->next = naviD->sel_range_list;
    range_item->prev = NULL;
    naviD->sel_range_list = range_item;
  }
  else
  {
    range_prev->next = range_item;

    range_item->next = range_next;
    range_item->prev = range_prev;
  }

  if(range_next)
  {
    range_next->prev = range_item;
  }

}
