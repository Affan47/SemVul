bytesio_traverse(bytesio *self, visitproc visit, void *arg)
{
    Py_VISIT(self->dict);
    return 0;
}
