RemoveAllObservers()
{
  for ( std::list< Observer * >::iterator i = m_Observers.begin();
        i != m_Observers.end(); ++i )
    {
    delete ( *i );
    }
  m_Observers.clear();
}
