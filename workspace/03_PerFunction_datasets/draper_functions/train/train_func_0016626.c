job_find(uint64 job_id)
{
    job jh = NULL;
    int index = _get_job_hash_index(job_id);

    for (jh = all_jobs[index]; jh && jh->r.id != job_id; jh = jh->ht_next);

    return jh;
}
