tileAction()
{
  if (! d->tileAction)
    {
      d->tileAction = new QAction(tr("&Tile Windows"), this);
      connect(d->tileAction, SIGNAL(triggered(bool)),
              d->area, SLOT(tileSubWindows()) );
    }
  return d->tileAction;
}
