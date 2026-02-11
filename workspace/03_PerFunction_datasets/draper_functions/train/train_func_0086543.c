rb_io_nonblock_p(VALUE io)
{
    rb_io_t *fptr;
    GetOpenFile(io, fptr);
    if (io_nonblock_mode(fptr->fd) & O_NONBLOCK)
	return Qtrue;
    return Qfalse;
}
