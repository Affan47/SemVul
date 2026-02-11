edit_worklist_callback(struct widget *widget)
{
  struct global_worklist *pgwl = global_worklist_by_id(MAX_ID - widget->ID);

  if (NULL == option_dialog
      || ODM_WORKLIST != option_dialog->mode
      || NULL == pgwl) {
    return -1;
  }

  switch (Main.event.button.button) {
  case SDL_BUTTON_LEFT:

    option_dialog->worklist.edited_name = widget;
    popup_worklist_editor(NULL, pgwl);
    break;

  case SDL_BUTTON_RIGHT:
    {

      struct ADVANCED_DLG *advanced = option_dialog->advanced;
      bool scroll = (NULL != advanced->pActiveWidgetList);

      global_worklist_destroy(pgwl);
      del_widget_from_vertical_scroll_widget_list(advanced, widget);


      if (scroll && advanced->pActiveWidgetList == NULL) {
        int len = advanced->pScroll->pUp_Left_Button->size.w;

        widget = advanced->pEndActiveWidgetList->next;
        do {
          widget = widget->prev;
          widget->size.w += len;
          FREESURFACE(widget->gfx);
        } while(widget != advanced->pBeginActiveWidgetList);
      }

      redraw_group(option_dialog->begin_widget_list,
                   option_dialog->end_widget_list, 0);
      widget_mark_dirty(option_dialog->end_widget_list);
      flush_dirty();
    }
    break;
  }
  return -1;
}
