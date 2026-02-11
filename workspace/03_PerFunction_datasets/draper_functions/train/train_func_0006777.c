imclient_addcallback(struct imclient *imclient, ...)
#else
void imclient_addcallback(va_alist)
va_dcl
#endif
{
    va_list pvar;
    char *keyword;
    int flags;
    imclient_proc_t *proc;
    void *rock;
    int i;
#ifdef __STDC__
    va_start(pvar, imclient);
#else
    struct imclient *imclient;

    va_start(pvar);
    imclient = va_arg(pvar, struct imclient *);
#endif

    assert(imclient);

    while ((keyword = va_arg(pvar, char *))) {
	flags = va_arg(pvar, int);
	proc = va_arg(pvar, imclient_proc_t *);
	rock = va_arg(pvar, void *);


	for (i = 0; i < imclient->callback_num; i++) {
	    if (imclient->callback[i].flags == flags &&
		!strcmp(imclient->callback[i].keyword, keyword)) break;
	}


	if (i == imclient->callback_num) {
	    if (imclient->callback_num == imclient->callback_alloc) {
		imclient->callback_alloc += CALLBACKGROW;
		imclient->callback = (struct imclient_callback *)
		  xrealloc((char *)imclient->callback,
		   imclient->callback_alloc*sizeof (struct imclient_callback));
	    }
	    imclient->callback_num++;
	    imclient->callback[i].keyword = xstrdup(keyword);
	    imclient->callback[i].flags = flags;
	}

	imclient->callback[i].proc = proc;
	imclient->callback[i].rock = rock;
    }
    va_end(pvar);
}
