addStdWindowMenu(QMenuBar *menubar)
{
  QLuaIde *ide = QLuaIde::instance();
  if (!d->windowMenu)
    {
      d->windowMenu = new QMenu(tr("Windows","windows|"), this);
      connect(d->windowMenu, SIGNAL(aboutToShow()),
              d, SLOT(aboutToShowWindowMenu()) );
      connect(ide, SIGNAL(windowsChanged()),
              d, SLOT(fillWindowMenu()) );
    }
  if (d->windowMenu)
    {
      d->fillWindowMenu();
      return menubar->addMenu(d->windowMenu);
    }
  return 0;
}
