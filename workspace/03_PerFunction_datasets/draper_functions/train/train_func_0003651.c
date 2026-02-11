delay_q_take()
{
    job j = delay_q_peek();
    if (!j) {
        return 0;
    }
    heapremove(&j->tube->delay, j->heap_index);
    return j;
}
