init_strides_from_shape(Py_buffer *view)
{
    Py_ssize_t i;

    assert(view->ndim > 0);

    view->strides[view->ndim-1] = view->itemsize;
    for (i = view->ndim-2; i >= 0; i--)
        view->strides[i] = view->strides[i+1] * view->shape[i+1];
}
