SVGParseExtendedPath(xmlNodePtr svg, xmlNodePtr top) {


    xmlChar *outline;
    SplineSet *head = NULL;

    outline = _xmlGetProp(svg,(xmlChar *) "d");
    if ( outline!=NULL ) {
	head = SVGParsePath(outline);
	_xmlFree(outline);
    }
#if 0
    effect = _xmlGetProp(svg,(xmlChar *) "path-effect");
    spirooutline = _xmlGetProp(svg,(xmlChar *) "original-d");
    if ( effect!=NULL && spirooutline!=NULL && *effect=='#' ) {
	xmlNodePtr effect_type = XmlFindID(top,effect+1);
	xmlChar *type = NULL;
	if ( effect_type!=NULL &&
		(type=_xmlGetProp(effect_type,"effect"))!=NULL &&
		_xmlStrcmp(type,(xmlChar *) "spiro")==0 )
	    SVGAddSpiros(spirooutline,head);
	if ( type!=NULL )
	    _xmlFree(type);
    }
    if ( effect!=NULL )
	_xmlFree(effect);
    if ( spirooutline!=NULL )
	_xmlFree(spirooutline);
#endif
return( head );
}
