lockJNIGrefs(Thread *self, int type) {


    if(!tryLockVMLock(global_refs[type].lock, self)) {
        disableSuspend(self);
        lockVMLock(global_refs[type].lock, self);
        enableSuspend(self);
    }
    fastDisableSuspend(self);
}
