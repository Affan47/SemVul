__Pyx_InitStrings(__Pyx_StringTabEntry *t) {
    while (t->p) {
        *t->p = PyString_FromStringAndSize(t->s, t->n - 1);
        if (!*t->p)
            return -1;
        if (t->i)
            PyString_InternInPlace(t->p);
        ++t;
    }
    return 0;
}
