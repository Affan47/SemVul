onMotion(FXObject *, FXSelector, void * ptr)
{
  FXEvent * ev = static_cast<FXEvent *>(ptr);
  if (_scint->tryDrag) {
    _scint->tryDrag = false;
    handle(this, MKUINT(0, SEL_BEGINDRAG), 0);
  }
  if (isDragging()) {
    return handle(this, MKUINT(0, SEL_DRAGGED), ptr);
  }
  else {
    Point pt(ev->win_x, ev->win_y);
    _scint->ButtonMove(pt);
  }
  return 1;
}
