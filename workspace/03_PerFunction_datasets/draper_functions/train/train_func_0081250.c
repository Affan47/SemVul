AuDequeueEvents(FlowPtr flow)
{
    AuBlock l;
    EventQueuePtr p, next;

    l = AuBlockAudio();
    p = AuEventQueue;
    AuUnBlockAudio(l);

    while (p) {
        l = AuBlockAudio();
        next = p->next;
        AuUnBlockAudio(l);

        if (p->flow == flow) {
            l = AuBlockAudio();

            RemoveFromLinkedList(AuEventQueue, p);

            if (!AuEventQueue)
                AuEventQueueTail = NULL;

            AuUnBlockAudio(l);
            AuProtectedFree(p);
        }

        p = next;
    }
}
