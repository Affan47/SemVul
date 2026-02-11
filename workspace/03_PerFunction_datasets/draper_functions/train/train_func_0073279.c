free_task_queue(task_queue q)
{
    tqueue *tq = (tqueue *) q.ptr;

    tq->connected = 0;


    if (tq->reading)
	ensure_usage(tq);
}
