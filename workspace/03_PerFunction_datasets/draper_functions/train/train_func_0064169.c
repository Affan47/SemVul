mouseReleaseEvent(QMouseEvent *ev)
{
  QListWidgetItem *item = itemAt(ev->pos());
  if (item && ev->button() == Qt::RightButton) {

    emit showLayerBoxPopup(Vector(ev->globalPos().x(), ev->globalPos().y()),
			   IpeQ(item->text()));
  } else
    QListWidget::mouseReleaseEvent(ev);
}
