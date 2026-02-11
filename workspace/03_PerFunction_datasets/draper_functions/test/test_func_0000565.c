argf_eof()
{
    if (current_file) {
	if (init_p == 0) return Qtrue;
	ARGF_FORWARD();
	if (rb_io_eof(current_file)) {
	    return Qtrue;
	}
    }
    return Qfalse;
}
