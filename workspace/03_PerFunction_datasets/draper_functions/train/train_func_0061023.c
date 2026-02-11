lookup( Word *word,
			      const vector<Entity*>& entities ){
  vector<Word*> vec;
  for ( size_t p=0; p < entities.size(); ++p ){
    vec = entities[p]->select<Word>();
    if ( !vec.empty() ){
      if ( vec[0]->id() == word->id() ) {

	return vec;
      }
    }
  }
  vec.clear();
  return vec;
}
