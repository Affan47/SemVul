rb_file_s_basename(argc, argv)
    int argc;
    VALUE *argv;
{
    VALUE fname, fext, basename;
    char *name, *p;
#if defined DOSISH_DRIVE_LETTER || defined DOSISH_UNC
    char *root;
#endif
    int f;

    if (rb_scan_args(argc, argv, "11", &fname, &fext) == 2) {
	StringValue(fext);
    }
    StringValue(fname);
    if (RSTRING(fname)->len == 0 || !*(name = RSTRING(fname)->ptr))
	return fname;
    name = skipprefix(name);
#if defined DOSISH_DRIVE_LETTER || defined DOSISH_UNC
    root = name;
#endif
    while (isdirsep(*name))
	name++;
    if (!*name) {
	p = name - 1;
	f = 1;
#if defined DOSISH_DRIVE_LETTER || defined DOSISH_UNC
	if (name != root) {

	}
#ifdef DOSISH_DRIVE_LETTER
	else if (*p == ':') {
	    p++;
	    f = 0;
	}
#endif
#ifdef DOSISH_UNC
	else {
	    p = "/";
	}
#endif
#endif
    }
    else if (!(p = strrdirsep(name))) {
	if (NIL_P(fext) || !(f = rmext(name, StringValueCStr(fext)))) {
	    f = chompdirsep(name) - name;
	    if (f == RSTRING(fname)->len) return fname;
	}
	p = name;
    }
    else {
	while (isdirsep(*p)) p++;
	if (NIL_P(fext) || !(f = rmext(p, StringValueCStr(fext)))) {
	    f = chompdirsep(p) - p;
	}
    }
    basename = rb_str_new(p, f);
    OBJ_INFECT(basename, fname);
    return basename;
}
