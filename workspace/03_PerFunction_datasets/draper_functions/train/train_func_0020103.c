PyFF_LayerInfo_set_name(PyFF_LayerInfo *self,PyObject *value,void *closure) {
    if ( STRING_CHECK(value)) {
	free( self->sf->layers[self->layer].name );
	self->sf->layers[self->layer].name = copy(PyBytes_AsString(value));
return(0);
    }
    PyErr_Format(PyExc_TypeError,"Expected layer name");
return( -1 );
}
