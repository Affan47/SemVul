PyFF_Font_set_cidsubfont(PyFF_Font *self,PyObject *value,void *closure) {
    int i;
    SplineFont *cidmaster = self->fv->cidmaster, *sf;
    EncMap *map = self->fv->map;

    if ( cidmaster==NULL ) {
	PyErr_Format(PyExc_EnvironmentError, "Not a cid-keyed font");
return( -1 );
    }
    if ( STRING_CHECK(value)) {
	char *name = PyBytes_AsString(value);
	for ( i=cidmaster->subfontcnt-1; i>=0 && strcmp(name,cidmaster->subfonts[i]->fontname)!=0; ++i );
	if ( i<0 ) {
	    PyErr_Format(PyExc_EnvironmentError, "No subfont named %s", name);
return( -1 );
	}
    } else if ( PyInt_Check(value)) {
	i = PyInt_AsLong(value);
	if ( i<0 || i>=cidmaster->subfontcnt ) {
	    PyErr_Format(PyExc_EnvironmentError, "Subfont index %d out of bounds must be >=0 and <%d.", i, cidmaster->subfontcnt );
return( -1 );
	}
    } else {
	PyErr_Format(PyExc_TypeError, "Expected either a string (fontname) or an index when setting the subfont");
return( -1 );
    }

    sf = cidmaster->subfonts[i];

    MVDestroyAll(self->fv->sf);
    if ( sf->glyphcnt>self->fv->sf->glyphcnt ) {
	free(self->fv->selected);
	self->fv->selected = gcalloc(sf->glyphcnt,sizeof(char));
	if ( sf->glyphcnt>map->encmax )
	    map->map = grealloc(map->map,(map->encmax = sf->glyphcnt)*sizeof(int));
	if ( sf->glyphcnt>map->backmax )
	    map->backmap = grealloc(map->backmap,(map->backmax = sf->glyphcnt)*sizeof(int));
	for ( i=0; i<sf->glyphcnt; ++i )
	    map->map[i] = map->backmap[i] = i;
	map->enccount = sf->glyphcnt;
    }
    self->fv->sf = sf;
    if ( !no_windowing_ui ) {
	FVSetTitle(self->fv);
	FontViewReformatOne(self->fv);
    }
return( 0 );
}
