incorrection( ) const {

    FoliaElement *p = _parent;
    while( p ){
      if ( p->isinstance( Correction_t ) )
	return dynamic_cast<Correction*>(p);
      else if ( p->isinstance( Sentence_t ) )
	break;
      p = p->parent();
    }
    return 0;
  }
