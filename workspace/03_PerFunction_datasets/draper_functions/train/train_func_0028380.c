pf_display (pf_main_info_t *minfo)
{

        pf_stat_t       *stat = minfo->stat;
        struct timeval now, diff;
        double us, conn_per_sec;
        uint no_completed, no_failed;

        no_completed = stat_atomic_read (stat, no_completed);
        no_failed = stat_atomic_read (stat, no_failed);

        gettimeofday (&now, NULL);

        timersub (&now, &minfo->start_time, &diff);

        us = diff.tv_sec + diff.tv_sec/1000000.0;

        conn_per_sec = no_completed / us;

        fprintf (stdout, "completed %u/%u  %f conn/sec  "
                        "(fail %u)           \r",
                        no_completed, minfo->total_connections,
                        conn_per_sec, no_failed);
        fflush (stdout);
}
