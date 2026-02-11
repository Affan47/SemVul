PyFF_Glyph_set_rsb(PyFF_Glyph *self,PyObject *value,void *closure) {
    int val;
    DBounds b;

    val = PyInt_AsLong(value);
    if ( PyErr_Occurred()!=NULL )
return( -1 );

    SplineCharFindBounds(self->sc,&b);
    SCSynchronizeWidth(self->sc,rint( val+b.maxx ),self->sc->width,NULL);
    SCCharChangedUpdate(self->sc,ly_none);
return( 0 );
}
