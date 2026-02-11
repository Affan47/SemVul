WriteCatalog( MemBuffer &file ) {
  file.WriteS( id );


  vector<string>::iterator iter;
  unsigned long msg_len = 0;
  for ( iter = cat.begin(); iter != cat.end(); ++iter )
    msg_len += (*iter).size() + 1;

  file.Write32( msg_len );

  for ( iter = cat.begin(); iter != cat.end(); ++iter ) {
    file.WriteS( StringUtil::crypt(*iter) );
    file.Write8( '\0' );
  }

  return cat.size();
}
