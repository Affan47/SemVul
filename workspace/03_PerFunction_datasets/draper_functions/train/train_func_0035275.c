cx_string_truncate(cx_string *self, cxsize length)
{

    if (self == NULL) {
        return NULL;
    }

    self->sz = CX_MIN(length, self->sz);
    self->data[self->sz] = '\0';

    return self;

}
