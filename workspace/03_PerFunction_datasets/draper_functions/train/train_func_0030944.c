PyFF_unitShape(PyObject *self, PyObject *args) {
    int n=0;
    SplineSet *ss;
    PyObject *ret;

    if ( !PyArg_ParseTuple(args,"|i",&n) )
return( NULL );
    ss = UnitShape(n);
    ret = (PyObject *) ContourFromSS(ss,NULL);
    SplinePointListFree(ss);
return( ret );
}
