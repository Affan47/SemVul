initqueue(struct queue *q)
{
    struct requirements noreq = { 0, ALLMASK, 0 };
    struct initdata init = { NULL, 0 };
#ifdef DEBUG
    printf("\n\nInitializing queue\n");
#endif
    q->palettechg = NULL;
    if (!q->first->action->requirement(q->first, &noreq))
	return 0;
    if (!q->last->action->initialize(q->last, &init))
	return 0;
    q->isinitialized = 1;
#ifdef DEBUG
    printf("Correctly initialized\n");
#endif
    return 1;
}
