pq_pop(PriorityQueue *pq)
{
    if (pq->size > 0) {
        void *result = pq->heap[1];
        pq->heap[1] = pq->heap[pq->size];
        pq->heap[pq->size] = NULL;
        pq->size--;
        pq_down(pq);
        return result;
    }
    else {
        return NULL;
    }
}
