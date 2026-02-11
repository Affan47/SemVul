guiActivateEvent( KParts::GUIActivateEvent *event )
{
  if ( event->activated() )
  {
    emitSelectionChanged();
    emit d->m_extension->enableAction( "print", d->m_doc != 0 );

    if ( !d->m_settings->autoLoadImages() && d->m_paLoadImages )
    {
        QList<QAction*> lst;
        lst.append( d->m_paLoadImages );
        plugActionList( "loadImages", lst );
    }
  }
}
