keyPressEvent(QKeyEvent* event)
{
  if (event->key() == Qt::Key_Escape) {
    hideCurrentBarWidget();
    return;
  }
  QWidget::keyPressEvent(event);

}
