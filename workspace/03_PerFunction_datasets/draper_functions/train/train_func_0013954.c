expire_recent(time_t cutoff)
{
#if 0 && defined(DEBUG)
    cerr << "Running expire recent..." << endl;
    StackTimer t;
#endif

    try {
        AutoTransaction a;

        while (1)
        {
            Q q("SELECT Library.sid, Journal.played, "
                    "Journal.flags, Journal.time "
                    "FROM Journal INNER JOIN Library "
                    "ON Journal.uid = Library.uid "
                    "WHERE Journal.time > ? ORDER BY Journal.time ASC;");
            q << correlate_from;

            if (!q.next())
                break;

            int flags;
            time_t next, played;

            q >> from >> played >> flags >> next;
            from_weight = Flags::deltify(played, flags);

            if (next > cutoff)
                break;

            correlate_from = next + 1;

            if (from_weight == -1)
                continue;

            while (q.next())
            {
                q >> to >> played >> flags;
                to_weight = Flags::deltify(played, flags);
                expire_recent_helper();
            }
        }

        a.commit();
    }
    WARNIFFAILED();
}
