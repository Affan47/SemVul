keyReleaseEvent(DigitView* view, QKeyEvent* e)
{
  ASSERT_ENGAUGE(e != 0);
  switch (e->key())
  {
  case Qt::Key_Up:
  case Qt::Key_Down:
  case Qt::Key_Left:
  case Qt::Key_Right:

    ASSERT_ENGAUGE(view != 0);
    ASSERT_ENGAUGE(view->document() != 0);
    view->document()->finishMove();
    break;
  default:

    e->ignore();
    break;
  }
}
