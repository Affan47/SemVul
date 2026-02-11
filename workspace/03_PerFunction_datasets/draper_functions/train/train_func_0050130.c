setMaxId( FoliaElement *child ) {
    if ( !child->id().empty() && !child->xmltag().empty() ){
      vector<string> parts;
      size_t num = TiCC::split_at( child->id(), parts, "." );
      if ( num > 0 ){
	string val = parts[num-1];
	int i;
	try {
	  i = stringTo<int>( val );
	}
	catch ( exception ){

	  return;
	}
	map<string,int>::iterator it = maxid.find( child->xmltag() );
	if ( it == maxid.end() ){
	  maxid[child->xmltag()] = i;
	}
	else {
	  if ( it->second < i ){
	    it->second = i;
	  }
	}
      }
    }
  }
