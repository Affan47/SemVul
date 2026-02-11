app_ref(GSview *a)
{
    int refcount = ++(a->refcount);
    if (debug & DEBUG_DEV) {
	char buf[MAXSTR];
	snprintf(buf, sizeof(buf), "app refcount=%d\n", refcount);
	app_msg_len_nolock(a, buf, (int)strlen(buf));
    }
    return refcount;
}
