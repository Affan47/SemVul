krb5_vlog_msg(krb5_context context,
	      krb5_log_facility *fac,
	      char **reply,
	      int level,
	      const char *fmt,
	      va_list ap)
     __attribute__((format (printf, 5, 0)))
{

    char *msg = NULL;
    const char *actual = NULL;
    char buf[64];
    time_t t = 0;
    int i;

    for(i = 0; fac && i < fac->len; i++)
	if(fac->val[i].min <= level &&
	   (fac->val[i].max < 0 || fac->val[i].max >= level)) {
	    if(t == 0) {
		t = time(NULL);
		krb5_format_time(context, t, buf, sizeof(buf), TRUE);
	    }
	    if(actual == NULL) {
		int ret = vasprintf(&msg, fmt, ap);
		if(ret < 0 || msg == NULL)
		    actual = fmt;
		else
		    actual = msg;
	    }
	    (*fac->val[i].log_func)(buf, actual, fac->val[i].data);
	}
    if(reply == NULL)
	free(msg);
    else
	*reply = msg;
    return 0;
}
