SetDefaultLanguage( const string &id ) {
  const Language *l = GetLanguage( id );

  if ( l ) lang = l;
  return l != 0;
}
