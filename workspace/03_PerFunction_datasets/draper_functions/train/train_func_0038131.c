RemoveObserver(unsigned long tag)
{
  for ( std::list< Observer * >::iterator i = m_Observers.begin();
        i != m_Observers.end(); ++i )
    {
    if ( ( *i )->m_Tag == tag )
      {
      delete ( *i );
      m_Observers.erase(i);
      m_ListModified = true;
      return;
      }
    }
}
