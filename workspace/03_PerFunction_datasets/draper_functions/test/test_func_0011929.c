PyFFFont_findEncodingSlot(PyObject *self, PyObject *args) {
    int uni= -1;
    char *name=NULL;
    FontViewBase *fv = ((PyFF_Font *) self)->fv;

    if ( !PyArg_ParseTuple(args,"s", &name ) ) {
	PyErr_Clear();
	if ( !PyArg_ParseTuple(args,"i", &uni ) )
return( NULL );
    }
    if ( uni<-1 || uni>=unicode4_size ) {
	PyErr_Format(PyExc_ValueError, "Unicode codepoint, %d, out of range, must be either -1 or between 0 and 0x10ffff", uni );
return( NULL );
    }

return( Py_BuildValue("i",SFFindSlot(fv->sf, fv->map, uni, name )) );
}
