PyFF_FontTuple(PyObject *self, PyObject *args) {
    FontViewBase *fv;
    int cnt;
    PyObject *tuple;

    for ( fv=FontViewFirst(), cnt=0; fv!=NULL; fv=fv->next, ++cnt );
    tuple = PyTuple_New(cnt);
    for ( fv=FontViewFirst(), cnt=0; fv!=NULL; fv=fv->next, ++cnt )
	PyTuple_SET_ITEM(tuple,cnt,PyFV_From_FV_I(fv));

return( tuple );
}
