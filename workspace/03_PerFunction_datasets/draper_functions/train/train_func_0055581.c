queue_init(Queue* q)
{
    *q = (Queue) malloc(sizeof(struct QueueRecord));
    if (*q == NULL) {
        syserr("malloc\n");
    }
    (*q)->first = NULL;
    (*q)->last = NULL;
    (*q)->size = 0;
}
