array_buffer_getbuf(arrayobject *self, Py_buffer *view, int flags)
{
    if (view==NULL) goto finish;

    view->buf = (void *)self->ob_item;
    view->obj = (PyObject*)self;
    Py_INCREF(self);
    if (view->buf == NULL)
        view->buf = (void *)emptybuf;
    view->len = (Py_SIZE(self)) * self->ob_descr->itemsize;
    view->readonly = 0;
    view->ndim = 1;
    view->itemsize = self->ob_descr->itemsize;
    view->suboffsets = NULL;
    view->shape = NULL;
    if ((flags & PyBUF_ND)==PyBUF_ND) {
        view->shape = &((Py_SIZE(self)));
    }
    view->strides = NULL;
    if ((flags & PyBUF_STRIDES)==PyBUF_STRIDES)
        view->strides = &(view->itemsize);
    view->format = NULL;
    view->internal = NULL;
    if ((flags & PyBUF_FORMAT) == PyBUF_FORMAT) {
        view->format = self->ob_descr->formats;
#ifdef Py_UNICODE_WIDE
        if (self->ob_descr->typecode == 'u') {
            view->format = "w";
        }
#endif
    }

 finish:
    self->ob_exports++;
    return 0;
}
