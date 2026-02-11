io_close(io)
    VALUE io;
{
    if (TYPE(io) == T_FILE) {
	rb_io_close(io);
	return Qnil;
    }
    return rb_funcall(io, rb_intern("close"), 0, 0);
}
