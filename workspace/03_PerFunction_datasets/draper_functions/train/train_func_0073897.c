actionCollection() const
{
  if ( !d->m_actionCollection )
  {
      d->m_actionCollection = new KActionCollection( this );
      d->m_actionCollection->setObjectName( "KXMLGUIClient-KActionCollection" );
  }
  return d->m_actionCollection;
}
