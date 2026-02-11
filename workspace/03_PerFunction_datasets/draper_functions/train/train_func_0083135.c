mmap_buffer_getbuf(mmap_object *self, Py_buffer *view, int flags)
{
    CHECK_VALID(-1);
    if (PyBuffer_FillInfo(view, (PyObject*)self, self->data, self->size,
                          (self->access == ACCESS_READ), flags) < 0)
        return -1;
    self->exports++;
    return 0;
}
