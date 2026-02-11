gm_set_window_cursor(FXWindow * window,FXCursor * cur) {
  window->setDefaultCursor(cur);
  window->setDragCursor(cur);
  FXWindow * child=window->getFirst();
  while(child) {
    child->setDefaultCursor(cur);
    child->setDragCursor(cur);
    child=child->getNext();
    }
  }
