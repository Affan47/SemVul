timerqueue_free(struct timerqueue * Q)
{
	struct timerrec * r;


	while ((r = ptrheap_getmin(Q->H)) != NULL) {
		free(r);
		ptrheap_deletemin(Q->H);
	}


	ptrheap_free(Q->H);


	free(Q);
}
