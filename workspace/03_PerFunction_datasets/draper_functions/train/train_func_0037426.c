JVM_RawMonitorExit(void *mon) {
    Thread *self = threadSelf();

    TRACE("JVM_RawMonitorExit(mon=%p)", mon);

    unlockVMLock(*(VMLock*)mon, self);
}
