statusBar() const
{
  if ( !d->m_statusBar )  {
    KParts::ReadOnlyPart* part = qobject_cast<KParts::ReadOnlyPart*>(parent());
    QWidget* w = part ? part->widget() : 0;
    KMainWindow* mw = w ? qobject_cast<KMainWindow *>( w->topLevelWidget() ) : 0;
    if ( mw )
      d->m_statusBar = mw->statusBar();
  }
  return d->m_statusBar;
}
