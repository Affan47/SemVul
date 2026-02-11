PyFFLayer_Round(PyFF_Layer *self, PyObject *args) {
    double factor=1;
    int i,j;
    PyFF_Contour *cntr;

    if ( !PyArg_ParseTuple(args,"|d",&factor ) )
return( NULL );
    for ( i=0; i<self->cntr_cnt; ++i ) {
	cntr = self->contours[i];
	for ( j=0; j<cntr->pt_cnt; ++j ) {
	    cntr->points[j]->x = rint( factor*cntr->points[j]->x )/factor;
	    cntr->points[j]->y = rint( factor*cntr->points[j]->y )/factor;
	}
    }
Py_RETURN( self );
}
