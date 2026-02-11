dockBack()
{
  if( formerBrotherDockWidget) {

    bool found = false;
    QList<K3DockWidget *> cl = findChildren<K3DockWidget *>();
	foreach ( K3DockWidget *obj, cl ) {
		while ( !found && obj!= 0 ) {
  		QWidget* widg = qobject_cast<QWidget*>(obj);
			if( widg == formerBrotherDockWidget)
				found = true;
		}
	}

    if( !found) {

      manualDock( formerBrotherDockWidget, formerDockPos, d->splitPosInPercent, QPoint(0,0), false, d->index);
      formerBrotherDockWidget = 0L;
      makeDockVisible();
      return;
    }
  }


  manualDock( ((K3DockMainWindow*)manager->main)->getMainDockWidget(), formerDockPos, d->splitPosInPercent, QPoint(0,0), false, d->index);
  formerBrotherDockWidget = 0L;
  if (parent())
    makeDockVisible();
}
