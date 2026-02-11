xml( bool recursive, bool kanon ) const {
    xmlNode *e = XmlNewNode( foliaNs(), _xmltag );
    KWargs attribs = collectAttributes();
    set<FoliaElement *> skipelements;
    vector<FoliaElement*>::const_iterator it=data.begin();
    while ( it != data.end() ){
      string at = tagToAtt( *it );
      if ( !at.empty() ){
	attribs[at] = (*it)->cls();
	skipelements.insert( *it );
      }
      ++it;
    }
    addAttributes( e, attribs );
    if ( recursive ){


      list<FoliaElement *> textelements;
      list<FoliaElement *> otherelements;
      multimap<ElementType, FoliaElement *> otherelementsMap;
      vector<FoliaElement*>::const_iterator it=data.begin();
      while ( it != data.end() ){
	if ( skipelements.find(*it) == skipelements.end() ){
	  if ( (*it)->isinstance(TextContent_t) ){
	    if ( (*it)->_class == "current" )
	      textelements.push_front( *it );
	    else
	      textelements.push_back( *it );
	  }
	  else {
	    if ( kanon )
	      otherelementsMap.insert( make_pair( (*it)->element_id(), *it ) );
	    else
	      otherelements.push_back( *it );
	  }
	}
	++it;
      }
      list<FoliaElement*>::const_iterator lit=textelements.begin();
      while ( lit != textelements.end() ){
	xmlAddChild( e, (*lit)->xml( recursive, kanon ) );
	++lit;
      }
      if ( !kanon ){
	list<FoliaElement*>::const_iterator lit=otherelements.begin();
	while ( lit != otherelements.end() ){
	  xmlAddChild( e, (*lit)->xml( recursive, kanon ) );
	  ++lit;
	}
      }
      else {
	multimap<ElementType, FoliaElement*>::const_iterator lit
	  = otherelementsMap.begin();
	while ( lit != otherelementsMap.end() ){
	  xmlAddChild( e, (lit->second)->xml( recursive, kanon ) );
	  ++lit;
	}
      }
    }
    return e;
  }
