current_VMReclaim(i_ctx_t *i_ctx_p)
{
    gs_memory_gc_status_t gstat, lstat;

    gs_memory_gc_status(iimemory_global, &gstat);
    gs_memory_gc_status(iimemory_local, &lstat);
    return (!gstat.enabled ? -2 : !lstat.enabled ? -1 : 0);
}
