progress_func (void *clientp, double dltotal, double dlnow,
			  double ultotal, double ulnow)
{
    urlinfo *u = (urlinfo *) clientp;
    int ret = 0;

    if (u->progfunc != NULL && dltotal > 0) {
	if (!u->pstarted) {
	    u->progfunc((long) dlnow, (long) dltotal, SP_LOAD_INIT);
	    u->pstarted = 1;
	} else {
	    ret = u->progfunc((long) dlnow, (long) dltotal, SP_TOTAL);
	}
    }

    return (ret == SP_RETURN_CANCELED) ? 1 : 0;
}
