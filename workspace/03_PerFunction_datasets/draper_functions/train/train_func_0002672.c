group_set_area(struct widget *pBeginGroupWidgetList,
		    struct widget *pEndGroupWidgetList,
                    SDL_Rect area)
{
  struct widget *pWidget = pEndGroupWidgetList;

  while (pWidget) {
    widget_set_area(pWidget, area);

    if(pWidget == pBeginGroupWidgetList) {
      break;
    }

    pWidget = pWidget->prev;
  }
}
