w_more(int c, WFILE *p)
{
    Py_ssize_t size, newsize;
    if (p->str == NULL)
        return;
    size = PyString_Size(p->str);
    newsize = size + size + 1024;
    if (newsize > 32*1024*1024) {
        newsize = size + (size >> 3);
    }
    if (_PyString_Resize(&p->str, newsize) != 0) {
        p->ptr = p->end = NULL;
    }
    else {
        p->ptr = PyString_AS_STRING((PyStringObject *)p->str) + size;
        p->end =
            PyString_AS_STRING((PyStringObject *)p->str) + newsize;
        *p->ptr++ = Py_SAFE_DOWNCAST(c, int, char);
    }
}
