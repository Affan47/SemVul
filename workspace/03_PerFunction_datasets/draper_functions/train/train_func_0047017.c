Invalidate( vtkExodusIICacheKey key, vtkExodusIICacheKey pattern )
{
  vtkExodusIICacheRef it;
  int nDropped = 0;
  it = this->Cache.begin();
  while ( it != this->Cache.end() )
    {
    if ( ! it->first.match( key, pattern ) )
      {
      ++it;
      continue;
      }

#ifdef VTK_EXO_DBG_CACHE
    cout << "Dropping " << VTK_EXO_PRT_KEY( it->first ) << VTK_EXO_PRT_ARR( it->second->Value ) << "\n";
#endif
    this->LRU.erase( it->second->LRUEntry );
    if ( it->second->Value )
      {
      this->Size -= it->second->Value->GetActualMemorySize() / 1024.;
      }
    vtkExodusIICacheRef tmpIt = it++;
    delete tmpIt->second;
    this->Cache.erase( tmpIt );

    if ( this->Size <= 0 )
      {
      if ( this->Cache.size() == 0 )
        this->Size = 0.;
      else
        this->RecomputeSize();
      }

    ++nDropped;
    }
  return nDropped;
}
