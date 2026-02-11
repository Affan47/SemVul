searchValue ( string value )
{


  string foundValue;


  for ( vector<stringHasher>:: iterator l_hasher=m_hasher.begin() ; l_hasher!=m_hasher.end() ; l_hasher++ ) {
    foundValue= ( *l_hasher ).getValue();
    if ( foundValue.compare ( value ) == 0 ) {
      return ( *l_hasher ).getKey();
    }
  }
  return "";
}
