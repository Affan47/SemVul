errmsg_get_with_default (int err)
{
    const char *ret = "";

#if EDEBUG
    fprintf(stderr, "errmsg_get_with_default: msg='%s'\n",
	    gretl_errmsg);
#endif

    if (*gretl_errmsg != '\0') {
	ret = gretl_errmsg;
    } else {
	const char *deflt = look_up_errmsg(err);

	if (deflt != NULL) {
	    ret = _(deflt);
	}
    }

    return ret;
}
