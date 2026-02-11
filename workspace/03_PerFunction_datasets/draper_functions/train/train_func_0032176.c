combo_popup(struct widget *combo)
{
  struct combo_menu *menu;
  struct widget *window, *label = NULL;
  int longest = 0, h = 0, x, y;

  fc_assert_ret(NULL != combo);
  fc_assert_ret(WT_COMBO == get_wtype(combo));

  if (NULL != combo->private_data.ptr) {
    return;
  }

  if (0 >= strvec_size(combo->data.vector)) {
    return;
  }


  window = create_window_skeleton(NULL, NULL, 0);
  window->action = combo_menu_callback;
  window->data.widget = combo;
  set_wstate(window, FC_WS_NORMAL);
  add_to_gui_list(ID_COMBO_MENU, window);


  strvec_iterate(combo->data.vector, string) {
    label = create_iconlabel_from_chars(NULL, window->dst, string,
                                       adj_font(10), WF_RESTORE_BACKGROUND);
    label->action = combo_menu_item_callback;
    label->data.widget = combo;
    set_wstate(label, FC_WS_NORMAL);
    add_to_gui_list(ID_LABEL, label);

    longest = MAX(longest, label->size.w);
    widget_set_position(label, adj_size(10), h);
    h += adj_size(15);
  } strvec_iterate_end;


  resize_window(window, NULL, NULL, longest + 2 * adj_size(10), h);

  x = combo->size.x + combo->dst->dest_rect.x;
  if (x + window->size.w > Main.screen->w) {
    x = Main.screen->w - window->size.w;
  }
  if (x < 0) {
    x = 0;
  }

  y = combo->size.y - h + combo->dst->dest_rect.y;
  if (y + window->size.h > Main.screen->h) {
    y = Main.screen->h - window->size.h;
  }
  if (y < 0) {
    y = 0;
  }

  widget_set_position(window, x, y);


  menu = fc_malloc(sizeof(*menu));
  menu->begin_widget_list = label;
  menu->end_widget_list = window;
  combo->private_data.ptr = menu;


  redraw_group(menu->begin_widget_list, menu->end_widget_list, 0);
  widget_mark_dirty(window);
  flush_dirty();
}
