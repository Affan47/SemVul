activate(QWidget *c0, QWidget *c1)
{
  if ( c0 ) child0 = c0;
  if ( c1 ) child1 = c1;

  setupMinMaxSize();

  delete divider;
  divider = new QFrame(this, "pannerdivider");
  divider->setFrameStyle(QFrame::Panel | QFrame::Raised);
  divider->setLineWidth(1);
  divider->raise();

  if (m_orientation == Qt::Horizontal)
    divider->setCursor(QCursor(Qt::SizeVerCursor));
  else
    divider->setCursor(QCursor(Qt::SizeHorCursor));
  divider->installEventFilter(this);

  initialised= true;

  updateName();
  divider->show();


  resizeEvent(0);


  K3DockWidget* dw0 = (K3DockWidget*) child0;
  K3DockWidget* dw1 = (K3DockWidget*) child1;


  if( fixedWidth0 != -1 || fixedHeight0 != -1 ) restoreFromForcedFixedSize( dw0 );
  if( fixedWidth1 != -1 || fixedHeight1 != -1 ) restoreFromForcedFixedSize( dw1 );


  if( dw0->forcedFixedWidth() != -1 ) {
    setForcedFixedWidth( dw0, dw0->forcedFixedWidth() );
  }
  else if( dw1->forcedFixedWidth() != -1 ) {
    setForcedFixedWidth( dw1, dw1->forcedFixedWidth() );
  }

  if( dw0->forcedFixedHeight() != -1 ) {
    setForcedFixedHeight (dw0, dw0->forcedFixedHeight() );
  }
  else if( dw1->forcedFixedHeight() != -1 ) {
    setForcedFixedHeight( dw1, dw1->forcedFixedHeight() );
  }
}
