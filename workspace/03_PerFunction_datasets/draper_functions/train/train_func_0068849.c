click_maybe_define(const char *arg, ErrorHandler *errh)
{
    for (const char *s = arg; *s; s++)
	if (*s == '=' && s > arg) {
	    if (!global_scope.define(String(arg, s), s + 1, true)) {
		if (errh)
		    errh->error("parameter %<%.*s%> multiply defined", s - arg, arg);
		return -1;
	    } else
		return 1;
	} else if (!isalnum((unsigned char) *s) && *s != '_')
	    break;
    return 0;
}
