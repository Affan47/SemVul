docall(obj)
register struct obj *obj;
{
	char buf[BUFSZ], qbuf[QBUFSZ];
	struct obj otemp;
	register char **str1;

	if (!obj->dknown) return;
	otemp = *obj;
	otemp.quan = 1L;
	otemp.onamelth = 0;
	otemp.oxlth = 0;
	if (objects[otemp.otyp].oc_class == POTION_CLASS && otemp.fromsink)

	    Sprintf(qbuf,"Call a stream of %s fluid:",
		    OBJ_DESCR(objects[otemp.otyp]));
	else
	    Sprintf(qbuf, "Call %s:", an(xname(&otemp)));
	getlin(qbuf, buf);
	if(!*buf || *buf == '\033')
		return;


	str1 = &(objects[obj->otyp].oc_uname);
	if(*str1) free((genericptr_t)*str1);


	(void)mungspaces(buf);
	if (!*buf) {
	    if (*str1) {


		*str1 = (char *)0;
		undiscover_object(obj->otyp);
	    }
	} else {
	    *str1 = strcpy((char *) alloc((unsigned)strlen(buf)+1), buf);
	    discover_object(obj->otyp, FALSE, TRUE);
	}
}
