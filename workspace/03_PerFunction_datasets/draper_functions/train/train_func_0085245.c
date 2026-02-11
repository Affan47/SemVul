dragEnterEvent(QDragEnterEvent *event)
{
  if (toolBarsEditable() && event->proposedAction() & (Qt::CopyAction | Qt::MoveAction) &&
       event->mimeData()->hasFormat("application/x-kde-action-list")) {
    QByteArray data = event->mimeData()->data("application/x-kde-action-list");

    QDataStream stream(data);

    QStringList actionNames;

    stream >> actionNames;

    foreach (const QString& actionName, actionNames) {
      foreach (KActionCollection* ac, KActionCollection::allCollections()) {
        QAction* newAction = ac->action(actionName.toLatin1().constData());
        if (newAction) {
          d->actionsBeingDragged.append(newAction);
          break;
        }
      }
    }

    if (d->actionsBeingDragged.count()) {
      QAction* overAction = actionAt(event->pos());

      QFrame* dropIndicatorWidget = new QFrame(this);
      dropIndicatorWidget->resize(8, height() - 4);
      dropIndicatorWidget->setFrameShape(QFrame::VLine);
      dropIndicatorWidget->setLineWidth(3);

      d->dropIndicatorAction = insertWidget(overAction, dropIndicatorWidget);

      insertAction(overAction, d->dropIndicatorAction);

      event->acceptProposedAction();
      return;
    }
  }

  QToolBar::dragEnterEvent(event);
}
