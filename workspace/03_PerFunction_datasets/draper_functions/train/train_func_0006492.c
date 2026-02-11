GC_new_proc_inner(proc)
GC_mark_proc proc;
{
    int result = GC_n_mark_procs++;

    if (GC_n_mark_procs > MAX_MARK_PROCS) ABORT("Too many mark procedures");
    GC_mark_procs[result] = proc;
    return result;
}
