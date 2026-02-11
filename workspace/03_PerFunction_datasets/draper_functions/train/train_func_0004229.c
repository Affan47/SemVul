wordParts() const {
    vector<Word*> result;
    for ( size_t i=0; i < data.size(); ++i ){
      FoliaElement *pnt = data[i];
      if ( pnt->isinstance( Word_t ) )
	result.push_back( dynamic_cast<Word*>(pnt) );
      else if ( pnt->isinstance( Quote_t ) ){
	vector<Word*> v = pnt->wordParts();
	result.insert( result.end(), v.begin(),v.end() );
      }
      else {

      }
    }
    return result;
  }
