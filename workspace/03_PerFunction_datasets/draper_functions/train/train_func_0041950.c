PyFFFont_mergeLookups(PyObject *self, PyObject *args) {
    SplineFont *sf = ((PyFF_Font *) self)->fv->sf;
    char *lookup1, *lookup2;
    OTLookup *otl1, *otl2;
    struct lookup_subtable *sub;

    if ( !PyArg_ParseTuple(args,"ss", &lookup1, &lookup2 ))
return( NULL );

    otl1 = SFFindLookup(sf,lookup1);
    if ( otl1==NULL ) {
	PyErr_Format(PyExc_EnvironmentError, "No lookup named %s exists", lookup1 );
return( NULL );
    }
    otl2 = SFFindLookup(sf,lookup2);
    if ( otl2==NULL ) {
	PyErr_Format(PyExc_EnvironmentError, "No lookup named %s exists", lookup2 );
return( NULL );
    }
    if ( otl1->lookup_type != otl2->lookup_type ) {
	PyErr_Format(PyExc_EnvironmentError, "When merging two lookups they must be of the same type, but %s and %s are not", lookup1, lookup2);
return( NULL );
    }
    FLMerge(otl1,otl2);

    for ( sub = otl2->subtables; sub!=NULL; sub=sub->next )
	sub->lookup = otl1;
    if ( otl1->subtables==NULL )
	otl1->subtables = otl2->subtables;
    else {
	for ( sub=otl1->subtables; sub->next!=NULL; sub=sub->next );
	sub->next = otl2->subtables;
    }
    otl2->subtables = NULL;
    SFRemoveLookup(sf,otl2);
Py_RETURN( self );
}
