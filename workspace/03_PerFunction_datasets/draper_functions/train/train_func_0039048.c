PyFF_LayerInfo_set_background(PyFF_LayerInfo *self,PyObject *value,void *closure) {
    if ( PyInt_Check(value)) {
	int val = PyInt_AsLong(value)!=0;
	SplineFont *sf = self->sf;
	int layer = self->layer;
	if ( val!=sf->layers[layer].background )
	    SFLayerSetBackground(sf,layer,val);
return(0);
    }
    PyErr_Format(PyExc_TypeError,"Expected boolean value");
return( -1 );
}
