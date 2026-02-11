tabletEvent(QTabletEvent *ev)
{
  Vector globalPos(ev->hiResGlobalPos().x(), ev->hiResGlobalPos().y());
  QPointF hiPos = ev->hiResGlobalPos() - (ev->globalPos() - ev->pos());
  ev->accept();

  switch (ev->type()) {
  case QEvent::TabletPress:
    iGlobalPos = globalPos;
    computeFifi(hiPos.x(), hiPos.y());
    if (ev->pointerType() == QTabletEvent::Eraser) {
      if (iObserver)
	iObserver->canvasObserverMouseAction(Qt::XButton1 |
					     iAdditionalModifiers);
    } else if (iTool)
      iTool->mouseButton(Qt::LeftButton | iAdditionalModifiers, true);
    else if (iObserver)
      iObserver->canvasObserverMouseAction(Qt::LeftButton |
					   iAdditionalModifiers);
    break;
  case QEvent::TabletMove:
    if (ev->pressure() > 0.01) {
      computeFifi(hiPos.x(), hiPos.y());
      if (iTool)
	iTool->mouseMove();
      if (iObserver)
	iObserver->canvasObserverPositionChanged();
      break;
    }

  case QEvent::TabletRelease:
    iGlobalPos = globalPos;
    computeFifi(hiPos.x(), hiPos.y());
    if (iTool)
      iTool->mouseButton(Qt::LeftButton, false);
    break;
  default:
    ipeDebug("Unknown tablet event");
    break;
  }
}
