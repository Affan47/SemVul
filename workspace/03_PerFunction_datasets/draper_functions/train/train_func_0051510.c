add_async_request (struct devstruct *dev, uaecptr request)
{
	struct asyncreq *ar, *ar2;

	if (log_uaeserial)
		write_log (_T("%s:%d async request %x added\n"), getdevname(), dev->unit, request);

	uae_sem_wait (&async_sem);
	ar = xcalloc (struct asyncreq, 1);
	ar->request = request;
	if (!dev->ar) {
		dev->ar = ar;
	} else {
		ar2 = dev->ar;
		while (ar2->next)
			ar2 = ar2->next;
		ar2->next = ar;
	}
	uae_sem_post (&async_sem);
	return 1;
}
