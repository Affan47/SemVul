rb_io_reopen(int argc, VALUE *argv, VALUE file)
{
    VALUE fname, nmode;
    int oflags;
    rb_io_t *fptr;

    rb_secure(4);
    if (rb_scan_args(argc, argv, "11", &fname, &nmode) == 1) {
	VALUE tmp = rb_io_check_io(fname);
	if (!NIL_P(tmp)) {
	    return io_reopen(file, tmp);
	}
    }

    FilePathValue(fname);
    rb_io_taint_check(file);
    fptr = RFILE(file)->fptr;
    if (!fptr) {
	fptr = RFILE(file)->fptr = ALLOC(rb_io_t);
	MEMZERO(fptr, rb_io_t, 1);
    }

    if (!NIL_P(nmode)) {
	int fmode = rb_io_modestr_fmode(StringValueCStr(nmode));
	if (IS_PREP_STDIO(fptr) &&
            ((fptr->mode & FMODE_READWRITE) & (fmode & FMODE_READWRITE)) !=
            (fptr->mode & FMODE_READWRITE)) {
	    rb_raise(rb_eArgError,
		     "%s can't change access mode from \"%s\" to \"%s\"",
		     PREP_STDIO_NAME(fptr), rb_io_fmode_modestr(fptr->mode),
		     rb_io_fmode_modestr(fmode));
	}
	fptr->mode = fmode;
	rb_io_mode_enc(fptr, StringValueCStr(nmode));
        fptr->encs.ecflags = 0;
        fptr->encs.ecopts = Qnil;
    }

    fptr->pathv = rb_str_new_frozen(fname);
    oflags = rb_io_fmode_oflags(fptr->mode);
    if (fptr->fd < 0) {
        fptr->fd = rb_sysopen(fptr->pathv, oflags, 0666);
	fptr->stdio_file = 0;
	return file;
    }

    if (fptr->mode & FMODE_WRITABLE) {
        if (io_fflush(fptr) < 0)
            rb_sys_fail(0);
    }
    fptr->rbuf.off = fptr->rbuf.len = 0;

    if (fptr->stdio_file) {
        if (freopen(RSTRING_PTR(fptr->pathv), rb_io_oflags_modestr(oflags), fptr->stdio_file) == 0) {
            rb_sys_fail_path(fptr->pathv);
        }
        fptr->fd = fileno(fptr->stdio_file);
#ifdef USE_SETVBUF
        if (setvbuf(fptr->stdio_file, NULL, _IOFBF, 0) != 0)
            rb_warn("setvbuf() can't be honoured for %s", RSTRING_PTR(fptr->pathv));
#endif
    }
    else {
        if (close(fptr->fd) < 0)
            rb_sys_fail_path(fptr->pathv);
        fptr->fd = -1;
        fptr->fd = rb_sysopen(fptr->pathv, oflags, 0666);
    }

    return file;
}
