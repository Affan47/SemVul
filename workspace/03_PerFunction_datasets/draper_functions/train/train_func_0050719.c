kick_buried_jobs(Srv *s, tube t, uint n)
{
    uint i;
    for (i = 0; (i < n) && kick_buried_job(s, t); ++i);
    return i;
}
