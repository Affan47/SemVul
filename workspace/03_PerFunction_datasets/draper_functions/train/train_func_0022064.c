removeListener ( TestListener *listener )
{
  ExclusiveZone zone( m_syncObject );
  removeFromSequence( m_listeners, listener );
}
