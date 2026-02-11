PyFFContour_AddExtrema(PyFF_Contour *self, PyObject *args) {
    int emsize = 1000;
    char *flag = NULL;
    int ae = ae_only_good;
    SplineSet *ss;

    if ( !PyArg_ParseTuple(args,"|si", &flag, &emsize ) )
return( NULL );
    if ( flag!=NULL )
	ae = FlagsFromString(flag,addextremaflags);
    if ( ae==PYFF_FLAG_UNKNOWN )
return( NULL );

    ss = SSFromContour(self,NULL);
    if ( ss==NULL )
Py_RETURN( self );
    SplineSetAddExtrema(NULL,ss,ae,emsize);
    ContourFromSS(ss,self);
    SplinePointListFree(ss);
Py_RETURN( self );
}
