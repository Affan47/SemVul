setTopLevel( bool isTopLevel )
{
  d->topLevel = isTopLevel;
  if ( isTopLevel ){
    K3DockWidget* par = (K3DockWidget*)parent();
    if( par && par->isDockBackPossible() )
        dockbackButton->show();
    else
        dockbackButton->hide();

    stayButton->hide();
    closeButton->hide();
    d->toDesktopButton->hide();
    drag->setEnabled( true );
  } else {
    dockbackButton->hide();
    stayButton->hide();
    if (!d->forceCloseButtonHidden) closeButton->show();
    if( d->showToDesktopButton )
      d->toDesktopButton->show();
  }
  layout->activate();

   bool dontShowDummy=drag->isVisibleTo(this) || dockbackButton->isVisibleTo(this) ||
        d->toDesktopButton->isVisibleTo(this) || stayButton->isVisibleTo(this) ||
        closeButton->isVisibleTo(this);
   for (Q3PtrListIterator<K3DockButton_Private> it( d->btns );it.current();++it) {
        dontShowDummy=dontShowDummy || (it.current()->isVisibleTo(this));
   }
   if (dontShowDummy) d->dummy->hide(); else d->dummy->show();

  updateGeometry();
}
