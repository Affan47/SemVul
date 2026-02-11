replica_set_tombstone_reap_stop(Replica *r, PRBool val)
{
    if (r == NULL)
        return;

	PR_Lock(r->repl_lock);
	r->tombstone_reap_stop = val;
	PR_Unlock(r->repl_lock);
}
