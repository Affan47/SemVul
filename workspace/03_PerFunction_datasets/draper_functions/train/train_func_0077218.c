load_wait(ftptr)
    char *ftptr;
{
    st_data_t th;

    if (!loading_tbl) return Qfalse;
    if (!st_lookup(loading_tbl, (st_data_t)ftptr, &th)) return Qfalse;
    do {
	if ((rb_thread_t)th == curr_thread) return Qtrue;
	CHECK_INTS;
    } while (st_lookup(loading_tbl, (st_data_t)ftptr, &th));
    return Qtrue;
}
