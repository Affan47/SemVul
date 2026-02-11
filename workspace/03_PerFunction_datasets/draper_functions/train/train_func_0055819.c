PyFFFont_Transform(PyFF_Layer *self, PyObject *args) {
    FontViewBase *fv = ((PyFF_Font *) self)->fv;
    int i;
    double m[6];
    real t[6];
    BVTFunc bvts[1];

    if ( !PyArg_ParseTuple(args,"(dddddd)",&m[0], &m[1], &m[2], &m[3], &m[4], &m[5] ) )
return( NULL );
    for ( i=0; i<6; ++i )
	t[i] = m[i];
    bvts[0].func = bvt_none;
    FVTransFunc(fv,t,0,bvts,true);
Py_RETURN( self );
}
