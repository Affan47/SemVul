SetZone( size_t startPos, size_t endPos )
{
  VERBOSE(3,"SETTING zone " << startPos << "-" << endPos << std::endl);
  std::vector< size_t > newZone;
  newZone.push_back( startPos );
  newZone.push_back( endPos );
  m_zone.push_back( newZone );
  m_active = true;
}
