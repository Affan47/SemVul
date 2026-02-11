addrinfo_mark(void *ptr)
{
    rb_addrinfo_t *rai = ptr;
    if (rai) {
        rb_gc_mark(rai->inspectname);
        rb_gc_mark(rai->canonname);
    }
}
