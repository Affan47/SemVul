mq_local_new ()
{
        quota_local_t  *local   = NULL;

        local = mem_get0 (THIS->local_pool);
        if (!local)
                goto out;

        local->ref = 1;
        LOCK_INIT (&local->lock);

        local->ctx = NULL;
        local->contri = NULL;

out:
        return local;
}
