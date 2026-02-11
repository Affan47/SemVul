stress_pq(tst_case * tc, void *data)
{
    int i;
    char buf[100], *prev, *curr;
    PriorityQueue *pq = pq_new(PQ_STRESS_SIZE, (lt_ft)&str_lt, &free);
    (void)data;

    for (i = 0; i < PQ_STRESS_SIZE; i++) {
        sprintf(buf, "<%d>", rand());
        pq_push(pq, estrdup(buf));
    }
    Aiequal(PQ_STRESS_SIZE, pq->size);

    prev = (char *) pq_pop(pq);
    for (i = 0; i < PQ_STRESS_SIZE - 1; i++) {
        curr = (char *) pq_pop(pq);
        if (str_lt(curr, prev) == true) {
            Assert(false, "previous should be less than or equal to current");
            Tmsg("%d: %s, %s\n", i, prev, curr);
        }
        free(prev);
        prev = curr;
    }
    free(prev);
    pq_clear(pq);
    pq_destroy(pq);
}
