stringio_close(stringio *self)
{
    self->closed = 1;

    if (resize_buffer(self, 0) < 0)
        return NULL;
    Py_CLEAR(self->readnl);
    Py_CLEAR(self->writenl);
    Py_CLEAR(self->decoder);
    Py_RETURN_NONE;
}
