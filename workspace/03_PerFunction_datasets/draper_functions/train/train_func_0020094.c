down_scroll_widget_list(struct ScrollBar *pVscroll,
				    struct widget *pBeginActiveWidgetLIST,
				    struct widget *pBeginWidgetLIST,
				    struct widget *pEndWidgetLIST)
{
  struct UP_DOWN pDown;
  struct widget *pBegin = pBeginActiveWidgetLIST;
  int step = pVscroll->active * pVscroll->step - 1;

  while (step--) {
    pBegin = pBegin->prev;
  }

  pDown.step = get_step(pVscroll);
  pDown.pBegin = pBeginActiveWidgetLIST;
  pDown.pEnd = pBegin;
  pDown.pBeginWidgetLIST = pBeginWidgetLIST;
  pDown.pEndWidgetLIST = pEndWidgetLIST;
  pDown.pVscroll = pVscroll;

  gui_event_loop((void *)&pDown, inside_scroll_down_loop,
	NULL, NULL, NULL, scroll_mouse_button_up, NULL);

  return pDown.pBegin;
}
