getHasher ( string key )
{
  long searchKey = hashValue ( key );
  long foundKey;

  for ( vector<stringInfosHasher>:: iterator l_hasher = m_hasher.begin() ; l_hasher != m_hasher.end() ; l_hasher++ ) {
    foundKey = ( *l_hasher ).getHashKey();
    if ( searchKey == foundKey ) {
      return ( *l_hasher );
    }
  }
  vector<string> tmp;
  stringInfosHasher defaut ( 0, "", tmp );
  return defaut;
}
