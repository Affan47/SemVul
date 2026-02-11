w_nbyte(const char *s, long n, struct dump_arg *arg)
{
    VALUE buf = arg->str;
    rb_str_buf_cat(buf, s, n);
    RBASIC(buf)->flags |= arg->infection;
    if (arg->dest && RSTRING_LEN(buf) >= BUFSIZ) {
	rb_io_write(arg->dest, buf);
	rb_str_resize(buf, 0);
    }
}
