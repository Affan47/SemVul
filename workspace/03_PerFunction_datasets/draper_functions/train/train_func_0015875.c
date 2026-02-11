RestoreInputReleaseDataFlags()
{
  for ( DataObjectPointerMap::iterator it = m_Inputs.begin(); it != m_Inputs.end(); ++it )
    {
    if ( it->second )
      {
      it->second->SetReleaseDataFlag(m_CachedInputReleaseDataFlags[it->first]);
      }
    }
  m_CachedInputReleaseDataFlags.clear();
}
