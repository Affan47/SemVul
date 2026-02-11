queue_get(QUEUE *q)
{
    BUFFER *buf;

    buf = queue_peek(q);
    if (buf) queue_remove(q,buf);
    return buf;
}
