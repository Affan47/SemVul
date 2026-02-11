eventNode(QEvent* event) {
    int x = 0;
    int y = 0;
    switch (event->type()) {
    case QEvent::ToolTip:
        {
          QHelpEvent* he = static_cast<QHelpEvent*>(event);
          x = he->x();
          y = he->y();
          break;
        }
    case QEvent::MouseButtonDblClick:
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseMove:
        {
          QMouseEvent* me = static_cast<QMouseEvent*>(event);
          x = me->x();
          y = me->y();
          break;
        }
    case QEvent::ContextMenu:
        {
          QContextMenuEvent* ce = static_cast<QContextMenuEvent*>(event);
          x = ce->x();
          y = ce->y();
          break;
        }
    default:
      return NULL;
    }
    QAbstractScrollArea* sa =
      static_cast<QAbstractScrollArea*>(parentWidget()->parentWidget());
    int xoff = sa->horizontalScrollBar()->value()/scale;
    int yoff = sa->verticalScrollBar()->value()/scale;

    BoundingBox bb = root->getBoundingBox();
    int w =
      static_cast<int>((bb.right-bb.left+Layout::extent)*scale);
    if (w < sa->viewport()->width())
      xoff -= (sa->viewport()->width()-w)/2;

    VisualNode* n;
    n = root->findNode(*na,
                       static_cast<int>(x/scale-xtrans+xoff),
                       static_cast<int>((y-30)/scale+yoff));
    return n;
  }
