rb_dlptr_plus(VALUE self, VALUE other)
{
    void *ptr;
    long num, size;

    ptr = rb_dlptr2cptr(self);
    size = RPTR_DATA(self)->size;
    num = NUM2LONG(other);
    return rb_dlptr_new((char *)ptr + num, size - num, 0);
}
