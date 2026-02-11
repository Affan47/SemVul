setDragPanel( K3DockWidgetHeaderDrag* nd )
{
  if ( !nd ) return;

  delete layout;
  layout = new QHBoxLayout( this );
  layout->setSizeConstraint( QLayout::Minimum );

  delete drag;
  drag = nd;
  if (drag->parentWidget()!=this) {
	drag->setParent(this);
        drag->move(0,0);
  }


  layout->addWidget( drag );
  layout->addWidget( dockbackButton );
  layout->addWidget( d->dummy );
  layout->addWidget( d->toDesktopButton );
  layout->addWidget( stayButton );
  bool dontShowDummy=drag->isVisibleTo(this) || dockbackButton->isVisibleTo(this) ||
	d->toDesktopButton->isVisibleTo(this) || stayButton->isVisibleTo(this) ||
	closeButton->isVisibleTo(this);
  for (Q3PtrListIterator<K3DockButton_Private> it( d->btns );it.current();++it) {
      layout->addWidget(it.current());
	dontShowDummy=dontShowDummy || (it.current()->isVisibleTo(this));
  }
  if (dontShowDummy) d->dummy->hide(); else d->dummy->show();
  layout->addWidget( closeButton );
  layout->activate();
  kDebug(282)<<"KdockWidgetHeader::setDragPanel:minimum height="<<layout->minimumSize().height();

  drag->setFixedHeight( closeButton->height());
}
