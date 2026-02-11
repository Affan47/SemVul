mouseReleaseEvent(QMouseEvent *event)
{

  if (d->dragAction) {
    d->dragAction = 0L;
    event->accept();
    return;
  }

  QToolBar::mouseReleaseEvent(event);
}
