reset_conn(conn c)
{
    connwant(c, 'r', &dirty);


    if (c->out_job && c->out_job->r.state == Copy) job_free(c->out_job);
    c->out_job = NULL;

    c->reply_sent = 0;
    c->state = STATE_WANTCOMMAND;
}
