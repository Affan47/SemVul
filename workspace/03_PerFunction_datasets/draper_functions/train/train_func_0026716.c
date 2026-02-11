wakeBlockingQueue(Capability *cap, StgBlockingQueue *bq)
{
    MessageBlackHole *msg;
    const StgInfoTable *i;

    ASSERT(bq->header.info == &stg_BLOCKING_QUEUE_DIRTY_info  ||
           bq->header.info == &stg_BLOCKING_QUEUE_CLEAN_info  );

    for (msg = bq->queue; msg != (MessageBlackHole*)END_TSO_QUEUE;
         msg = msg->link) {
        i = msg->header.info;
        if (i != &stg_IND_info) {
            ASSERT(i == &stg_MSG_BLACKHOLE_info);
            tryWakeupThread(cap,msg->tso);
        }
    }


#if defined(DEBUG) && !defined(THREADED_RTS)


    bq->bh = 0; bq->queue = 0; bq->owner = 0;
#endif
    OVERWRITE_INFO(bq, &stg_IND_info);
}
