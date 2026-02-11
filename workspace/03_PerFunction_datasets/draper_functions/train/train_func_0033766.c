timerqueue_getptr(struct timerqueue * Q, const struct timeval * tv)
{
	struct timerrec * r;
	void * ptr;


	if ((r = ptrheap_getmin(Q->H)) == NULL)
		return (NULL);


	if (tvcmp(&r->tv, tv) > 0)
		return (NULL);


	ptrheap_deletemin(Q->H);


	ptr = r->ptr;


	free(r);


	return (ptr);
}
