PyFFSelection_new(PyFF_Font *owner) {
    PyFF_Selection *self;

    if ( owner->selection != NULL )
Py_RETURN( owner->selection );
    self = PyObject_New(PyFF_Selection, &PyFF_SelectionType);
    self->fv = owner->fv;
    owner->selection = self;
    self->by_glyphs = 0;
Py_RETURN( self );
}
