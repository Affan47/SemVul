bench_stats_sum(pid_t ppid,
                                            struct wr_proc_task **childs,
                                            int childs_count)
{
    int i;
    char *tmp;
    struct wr_proc_task *child;
    struct wr_proc_task *st;
    struct wr_proc_task *final;

    final = wr_proc_stat(ppid);

    for (i = 0; i < childs_count; i++) {
        child = (childs)[i];

        st = wr_proc_stat(child->pid);

        final->wr_rss      += st->wr_rss;
        final->wr_utime_ms += st->wr_utime_ms;
        final->wr_stime_ms += st->wr_stime_ms;

        wr_proc_free(st);
    }


    final->wr_rss      /= (childs_count + 1);
    tmp = human_readable_size(final->wr_rss);
    free(final->wr_rss_hr);
    final->wr_rss_hr = tmp;
    final->wr_utime_ms /= (childs_count + 1);
    final->wr_stime_ms /= (childs_count + 1);

    return final;
}
