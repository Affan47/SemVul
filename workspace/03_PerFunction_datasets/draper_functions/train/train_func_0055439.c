hit_pq_up(PriorityQueue *pq)
{
    Hit **heap = (Hit **)pq->heap;
    Hit *node;
    int i = pq->size;
    int j = i >> 1;
    node = heap[i];

    while ((j > 0) && hit_lt(node, heap[j])) {
        heap[i] = heap[j];
        i = j;
        j = j >> 1;
    }
    heap[i] = node;
}
