PR_Calloc(PRUint32 nelem, PRUint32 elsize)
{
    if (!_pr_initialized) _PR_ImplicitInitialization();

    return use_zone_allocator ?
        pr_ZoneCalloc(nelem, elsize) : calloc(nelem, elsize);
}
