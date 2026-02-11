UFOLoadGlyphs(SplineFont *sf,char *glyphdir) {
    char *glyphlist = buildname(glyphdir,"contents.plist");
    xmlDocPtr doc;
    xmlNodePtr plist, dict, keys, value;
    char *valname, *glyphfname;
    int i;
    SplineChar *sc;
    int tot;

    doc = _xmlParseFile(glyphlist);
    free(glyphlist);
    if ( doc==NULL ) {
	LogError( _("Bad contents.plist\n" ));
return;
    }
    plist = _xmlDocGetRootElement(doc);
    dict = FindNode(plist->children,"dict");
    if ( _xmlStrcmp(plist->name,(const xmlChar *) "plist")!=0 || dict == NULL ) {
	LogError(_("Expected property list file"));
	_xmlFreeDoc(doc);
return;
    }
    for ( tot=0, keys=dict->children; keys!=NULL; keys=keys->next ) {
	if ( _xmlStrcmp(keys->name,(const xmlChar *) "key")==0 )
	    ++tot;
    }
    ff_progress_change_total(tot);
    for ( keys=dict->children; keys!=NULL; keys=keys->next ) {
	for ( value = keys->next; value!=NULL && _xmlStrcmp(value->name,(const xmlChar *) "text")==0;
		value = value->next );
	if ( value==NULL )
    break;
	if ( _xmlStrcmp(keys->name,(const xmlChar *) "key")==0 ) {
	    valname = (char *) _xmlNodeListGetString(doc,value->children,true);
	    glyphfname = buildname(glyphdir,valname);
	    free(valname);
	    sc = UFOLoadGlyph(glyphfname);
	    if ( sc!=NULL ) {
		sc->parent = sf;
		if ( sf->glyphcnt>=sf->glyphmax )
		    sf->glyphs = grealloc(sf->glyphs,(sf->glyphmax+=100)*sizeof(SplineChar *));
		sc->orig_pos = sf->glyphcnt;
		sf->glyphs[sf->glyphcnt++] = sc;
	    }
	    keys = value;
	    ff_progress_next();
	}
    }
    _xmlFreeDoc(doc);

    GlyphHashFree(sf);
    for ( i=0; i<sf->glyphcnt; ++i )
	UFORefFixup(sf,sf->glyphs[i]);
}
