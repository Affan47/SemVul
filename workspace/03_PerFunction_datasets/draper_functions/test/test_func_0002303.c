addMorph( MorphologyLayer *ml,
		     const vector<string>& lemmas ) const {
  int offset = 0;
  for ( size_t p=0; p < lemmas.size(); ++p ){
    Morpheme *m = new Morpheme();
#pragma omp critical(foliaupdate)
    {
      ml->append( m );
    }
    KWargs args;
    args["value"] = lemmas[p];
    args["offset"] = toString(offset);
    TextContent *t = new TextContent( args );
    offset += lemmas[p].length();
#pragma omp critical(foliaupdate)
    {
      m->append( t );
    }
  }
}
