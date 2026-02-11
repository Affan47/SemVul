del_widget_pointer_from_gui_list(struct widget *pGUI)
{
  if (!pGUI) {
    return;
  }

  if (pGUI == pBeginMainWidgetList) {
    pBeginMainWidgetList = pBeginMainWidgetList->next;
  }

  if (pGUI->prev && pGUI->next) {
    pGUI->prev->next = pGUI->next;
    pGUI->next->prev = pGUI->prev;
  } else {
    if (pGUI->prev) {
      pGUI->prev->next = NULL;
    }

    if (pGUI->next) {
      pGUI->next->prev = NULL;
    }

  }

  if (pSellected_Widget == pGUI) {
    pSellected_Widget = NULL;
  }
}
