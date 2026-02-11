getHasher ( string key )
{
  long searchKey=hashValue ( key );
  long foundKey;
  stringHasher defaut(0,"","");

  for ( vector<stringHasher>:: iterator l_hasher=m_hasher.begin() ; l_hasher!=m_hasher.end() ; l_hasher++ ) {
    foundKey= ( *l_hasher ).getHashKey();
    if ( searchKey == foundKey ) {
      return ( *l_hasher );
    }
  }
  return defaut;
}
