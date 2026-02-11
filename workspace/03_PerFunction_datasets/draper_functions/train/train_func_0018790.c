scheduleYield (Capability **pcap, Task *task)
{
    Capability *cap = *pcap;
    int didGcLast = rtsFalse;


    if (!shouldYieldCapability(cap,task,rtsFalse) &&
        (!emptyRunQueue(cap) ||
         !emptyInbox(cap) ||
         sched_state >= SCHED_INTERRUPTING)) {
        return;
    }


    do {
        didGcLast = yieldCapability(&cap,task, !didGcLast);
    }
    while (shouldYieldCapability(cap,task,didGcLast));


    *pcap = cap;
    return;
}
