adjustFSOrder(string & tag) {
    string::size_type sep = tag.find(">");
    string head = tag.substr(0, sep + 1);
    string products = tag.substr(sep + 1);
    OrderedParticles finalstate;
    bool loopbreak(true);
    while ( loopbreak ) {
      sep = products.find(",");
      string child;
      if( sep != string::npos ) {
	child = products.substr(0, sep);
	products = products.substr(sep + 1);
      }
      else {
	child = string(products.begin(), products.end() - 1);
	loopbreak = false;
      }
      PDPtr p = BaseRepository::GetObject<PDPtr>
	(string("/Herwig/Particles/" + child));
      if( p ) finalstate.insert(p);
    }
    if( finalstate.empty() ) return;
    tag = head;
    OrderedParticles::const_iterator iend = finalstate.end();
    OrderedParticles::size_type count(0), npr(finalstate.size());
    for( OrderedParticles::const_iterator it = finalstate.begin();
	 it != iend;  ++it ) {
      tag += (**it).name();
      if( ++count != npr ) tag += string(",");
    }
    tag += string(";");
   }
