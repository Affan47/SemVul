CBL_ERROR_PROC (unsigned char *x, unsigned char *pptr)
{
	struct handlerlist	*hp = NULL;
	struct handlerlist	*h = hdlrs;
	int			(**p)(char *s) = NULL;

	COB_CHK_PARMS (CBL_ERROR_PROC, 2);

	memcpy (&p, &pptr, sizeof (void *));
	if (!p || !*p) {
		return -1;
	}

	while (h != NULL) {
		if (h->proc == *p) {
			if (hp != NULL) {
				hp->next = h->next;
			} else {
				hdlrs = h->next;
			}
			if (hp) {
				free (hp);
			}
			break;
		}
		hp = h;
		h = h->next;
	}
	if (*x != 0) {
		return 0;
	}
	h = cob_malloc (sizeof(struct handlerlist));
	h->next = hdlrs;
	h->proc = *p;
	hdlrs = h;
	return 0;
}
