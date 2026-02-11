o_select_box_search(GSCHEM_TOPLEVEL *w_current)
{
  TOPLEVEL *toplevel = w_current->toplevel;
  OBJECT *o_current=NULL;
  int count = 0;
  int SHIFTKEY = w_current->SHIFTKEY;
  int CONTROLKEY = w_current->CONTROLKEY;
  int left, right, top, bottom;
  const GList *iter;

  left = min(w_current->first_wx, w_current->second_wx);
  right = max(w_current->first_wx, w_current->second_wx);
  top = min(w_current->first_wy, w_current->second_wy);
  bottom = max(w_current->first_wy, w_current->second_wy);

  iter = s_page_objects (toplevel->page_current);
  while (iter != NULL) {
    o_current = iter->data;

    if (o_is_visible (toplevel, o_current) || toplevel->show_hidden_text) {

      if ( o_current->w_left   >= left &&
           o_current->w_right  <= right  &&
           o_current->w_top    >= top  &&
           o_current->w_bottom <= bottom ) {

        o_select_object(w_current, o_current, MULTIPLE, count);
        count++;
      }
    }
    iter = g_list_next (iter);
  }


  if (count == 0 && !SHIFTKEY && !CONTROLKEY) {
    o_select_unselect_all (w_current);
  }
  i_update_menus(w_current);
}
