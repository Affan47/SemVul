span_schedule_next(span_sched_state_t *s)
{
    int i;
    uint64_t earliest;

    earliest = ~((uint64_t) 0);
    for (i = 0;  i < s->max_to_date;  i++)
    {
        if (s->sched[i].callback  &&  earliest > s->sched[i].when)
            earliest = s->sched[i].when;

    }

    return earliest;
}
