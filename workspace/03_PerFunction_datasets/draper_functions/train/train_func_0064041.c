co_sched_append(struct co_sched* sched, co_context_t ctx)
{
    struct run_queue* rq = &sched->run_queue;

    if (rq->tail) {
        rq->tail->next = ctx;
        ctx->prev = rq->tail;
    }
    rq->tail = ctx;

    if (!rq->head) {
        rq->head = ctx;
    }

    ctx->next = 0;
}
