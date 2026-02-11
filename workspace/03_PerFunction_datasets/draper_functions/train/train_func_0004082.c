traceSchedEvent_stderr (Capability *cap, EventTypeNum tag,
                                    StgTSO *tso,
                                    StgWord info1 STG_UNUSED,
                                    StgWord info2 STG_UNUSED)
{
    ACQUIRE_LOCK(&trace_utx);

    tracePreface();
    switch (tag) {
    case EVENT_CREATE_THREAD:
        debugBelch("cap %d: created thread %" FMT_Word "\n",
                   cap->no, (W_)tso->id);
        break;
    case EVENT_RUN_THREAD:
        debugBelch("cap %d: running thread %" FMT_Word " (%s)\n",
                   cap->no, (W_)tso->id, what_next_strs[tso->what_next]);
        break;
    case EVENT_THREAD_RUNNABLE:
        debugBelch("cap %d: thread %" FMT_Word " appended to run queue\n",
                   cap->no, (W_)tso->id);
        break;
    case EVENT_MIGRATE_THREAD:
        debugBelch("cap %d: thread %" FMT_Word " migrating to cap %d\n",
                   cap->no, (W_)tso->id, (int)info1);
        break;
    case EVENT_THREAD_WAKEUP:
        debugBelch("cap %d: waking up thread %" FMT_Word " on cap %d\n",
                   cap->no, (W_)tso->id, (int)info1);
        break;

    case EVENT_STOP_THREAD:
        if (info1 == 6 + BlockedOnBlackHole) {
            debugBelch("cap %d: thread %" FMT_Word " stopped (blocked on black hole owned by thread %lu)\n",
                       cap->no, (W_)tso->id, (long)info2);
        } else {
            debugBelch("cap %d: thread %" FMT_Word " stopped (%s)\n",
                       cap->no, (W_)tso->id, thread_stop_reasons[info1]);
        }
        break;
    default:
        debugBelch("cap %d: thread %" FMT_Word ": event %d\n\n",
                   cap->no, (W_)tso->id, tag);
        break;
    }

    RELEASE_LOCK(&trace_utx);
}
