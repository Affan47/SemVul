addNERTags( const vector<Word*>& words,
			    const vector<string>& tags,
			    const vector<double>& confs ){
  if ( words.empty() )
    return;
  EntitiesLayer *el = 0;
#pragma omp critical(foliaupdate)
  {
    Sentence *sent = words[0]->sentence();
    try {
      el = sent->annotation<EntitiesLayer>();
    }
    catch(...){
      el = new EntitiesLayer();
      sent->append( el );
    }
  }
  vector<Word*> stack;
  vector<double> dstack;
  string curNER;
  for ( size_t i=0; i < tags.size(); ++i ){
    if (debug)
      *Log(nerLog) << "NER = " << tags[i] << endl;
    vector<string> ner;
    if ( tags[i] == "O" ){
      if ( !stack.empty() ){
	if (debug) {
	  *Log(nerLog) << "O spit out " << curNER << endl;
	  using TiCC::operator<<;
	  *Log(nerLog) << "spit out " << stack << endl;
	}
	addEntity( el, tagset, stack, dstack, curNER );
	dstack.clear();
	stack.clear();
      }
      continue;
    }
    else {
      size_t num_words = TiCC::split_at( tags[i], ner, "-" );
      if ( num_words != 2 ){
	*Log(nerLog) << "expected <NER>-tag, got: " << tags[i] << endl;
	exit( EXIT_FAILURE );
      }
    }
    if ( ner[0] == "B" ||
	 ( ner[0] == "I" && stack.empty() ) ||
	 ( ner[0] == "I" && ner[1] != curNER ) ){


      if ( !stack.empty() ){
	if ( debug ){
	  *Log(nerLog) << "B spit out " << curNER << endl;
	  using TiCC::operator<<;
	  *Log(nerLog) << "spit out " << stack << endl;
	}
	addEntity( el, tagset, stack, dstack, curNER );
	dstack.clear();
	stack.clear();
      }
      curNER = ner[1];
    }
    dstack.push_back( confs[i] );
    stack.push_back( words[i] );
  }
  if ( !stack.empty() ){
    if ( debug ){
      *Log(nerLog) << "END spit out " << curNER << endl;
      using TiCC::operator<<;
      *Log(nerLog) << "spit out " << stack << endl;
    }
    addEntity( el, tagset, stack, dstack, curNER );
  }
}
