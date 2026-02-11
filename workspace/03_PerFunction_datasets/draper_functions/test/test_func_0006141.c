XMLEntryToPython(xmlDocPtr doc,xmlNodePtr entry) {
    char *contents;

    if ( _xmlStrcmp(entry->name,(const xmlChar *) "true")==0 ) {
	Py_INCREF(Py_True);
return( Py_True );
    }
    if ( _xmlStrcmp(entry->name,(const xmlChar *) "false")==0 ) {
	Py_INCREF(Py_False);
return( Py_False );
    }
    if ( _xmlStrcmp(entry->name,(const xmlChar *) "none")==0 ) {
	Py_INCREF(Py_None);
return( Py_None );
    }

    if ( _xmlStrcmp(entry->name,(const xmlChar *) "dict")==0 )
return( LibToPython(doc,entry));
    if ( _xmlStrcmp(entry->name,(const xmlChar *) "array")==0 ) {
	xmlNodePtr sub;
	int cnt;
	PyObject *ret, *item;


	for ( cnt=0, sub=entry->children; sub!=NULL; sub=sub->next ) {
	    if ( _xmlStrcmp(sub->name,(const xmlChar *) "text")==0 )
	continue;
	    ++cnt;
	}
	ret = PyTuple_New(cnt);
	for ( cnt=0, sub=entry->children; sub!=NULL; sub=sub->next ) {
	    if ( _xmlStrcmp(sub->name,(const xmlChar *) "text")==0 )
	continue;
	    item = XMLEntryToPython(doc,sub);
	    if ( item==NULL ) {
		item = Py_None;
		Py_INCREF(item);
	    }
	    PyTuple_SetItem(ret,cnt,item);
	    ++cnt;
	}
return( ret );
    }

    contents = (char *) _xmlNodeListGetString(doc,entry->children,true);
    if ( _xmlStrcmp(entry->name,(const xmlChar *) "integer")==0 ) {
	long val = strtol(contents,NULL,0);
	free(contents);
return( Py_BuildValue("i",val));
    }
    if ( _xmlStrcmp(entry->name,(const xmlChar *) "real")==0 ) {
	double val = strtod(contents,NULL);
	free(contents);
return( Py_BuildValue("d",val));
    }
    if ( _xmlStrcmp(entry->name,(const xmlChar *) "string")==0 ) {
	PyObject *ret = Py_BuildValue("s",contents);
	free(contents);
return( ret );
    }
    LogError(_("Unknown python type <%s> when reading UFO/GLIF lib data."), (char *) entry->name);
    free( contents );
return( NULL );
}
