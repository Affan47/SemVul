soonest_job(conn c)
{
    job j = NULL;
    job soonest = c->soonest_job;

    if (soonest == NULL) {
        for (j = c->reserved_jobs.next; j != &c->reserved_jobs; j = j->next) {
            if (j->r.deadline_at <= (soonest ? : j)->r.deadline_at) soonest = j;
        }
    }
    c->soonest_job = soonest;
    return soonest;
}
