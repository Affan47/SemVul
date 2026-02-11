dragMove( K3DockWidget* dw, QPoint pos )
{
  QPoint p = dw->mapToGlobal( dw->widget->pos() );
  K3DockWidget::DockPosition oldPos = curPos;

  QSize r = dw->widget->size();
  if ( dw->parentDockTabGroup() ){
    curPos = K3DockWidget::DockCenter;
    if ( oldPos != curPos ) {
      d->dragRect.setRect( p.x()+2, p.y()+2, r.width()-4, r.height()-4 );
    }
    return;
  }

  int w = r.width() / 3;
  int h = r.height() / 3;

  if ( pos.y() <= h ){
    curPos = K3DockWidget::DockTop;
    w = r.width();
  } else
    if ( pos.y() >= 2*h ){
      curPos = K3DockWidget::DockBottom;
      p.setY( p.y() + 2*h );
      w = r.width();
    } else
      if ( pos.x() <= w ){
        curPos = K3DockWidget::DockLeft;
        h = r.height();
      } else
        if ( pos.x() >= 2*w ){
          curPos = K3DockWidget::DockRight;
          p.setX( p.x() + 2*w );
          h = r.height();
        } else
          {
            curPos = K3DockWidget::DockCenter;
            p.setX( p.x() + w );
            p.setY( p.y() + h );
          }

  if ( oldPos != curPos ) {
    d->dragRect.setRect( p.x(), p.y(), w, h );
    drawDragRectangle();
  }
}
