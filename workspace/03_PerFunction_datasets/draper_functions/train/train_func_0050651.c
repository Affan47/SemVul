tailmatch(PyUnicodeObject *self,
              PyUnicodeObject *substring,
              Py_ssize_t start,
              Py_ssize_t end,
              int direction)
{
    if (substring->length == 0)
        return 1;

    ADJUST_INDICES(start, end, self->length);
    end -= substring->length;
    if (end < start)
        return 0;

    if (direction > 0) {
        if (Py_UNICODE_MATCH(self, end, substring))
            return 1;
    } else {
        if (Py_UNICODE_MATCH(self, start, substring))
            return 1;
    }

    return 0;
}
