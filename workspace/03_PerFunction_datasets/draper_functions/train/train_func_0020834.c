append( FoliaElement *child ){
    if ( child->isinstance(Sentence_t) )
      child->setAuth( false );
    FoliaElement::append( child );
    return child;
  }
