setAttributes( const KWargs& kwargsin ){
    KWargs kwargs = kwargsin;
    KWargs::const_iterator it;
    it = kwargs.find( "src" );
    if ( it != kwargs.end() ) {
      _src = it->second;
      kwargs.erase( "src" );
    }
    FoliaElement::setAttributes(kwargs);
  }
