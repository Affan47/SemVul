make_conn(int fd, char start_state, tube use, tube watch)
{
    job j;
    conn c;

    c = new(struct conn);
    if (!c) return twarn("OOM"), (conn) 0;

    ms_init(&c->watch, (ms_event_fn) on_watch, (ms_event_fn) on_ignore);
    if (!ms_append(&c->watch, watch)) {
        free(c);
        return twarn("OOM"), (conn) 0;
    }

    c->use = NULL;
    TUBE_ASSIGN(c->use, use);
    use->using_ct++;

    c->sock.fd = fd;
    c->state = start_state;
    c->type = 0;
    c->cmd_read = 0;
    c->pending_timeout = -1;
    c->soonest_job = NULL;
    c->in_job = c->out_job = NULL;
    c->in_job_read = c->out_job_sent = 0;
    c->prev = c->next = c;
    j = &c->reserved_jobs;
    j->prev = j->next = j;


    cur_conn_ct++;
    tot_conn_ct++;

    return c;
}
