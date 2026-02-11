Find( vtkExodusIICacheKey key )
{
  static vtkDataArray* dummy = 0;

  vtkExodusIICacheRef it = this->Cache.find( key );
  if ( it != this->Cache.end() )
    {
    this->LRU.erase( it->second->LRUEntry );
    it->second->LRUEntry = this->LRU.insert( this->LRU.begin(), it );
    return it->second->Value;
    }

  dummy = 0;
  return dummy;
}
