rb_dl_malloc(VALUE self, VALUE size)
{
    void *ptr;

    rb_secure(4);
    ptr = (void*)ruby_xmalloc(NUM2INT(size));
    return PTR2NUM(ptr);
}
