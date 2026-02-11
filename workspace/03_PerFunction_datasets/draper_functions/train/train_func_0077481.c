notify() {
    mutex.lock() ;
    OSThread_t me = OSThread::self() ;
    if (owner != me) {
        mutex.unlock() ;
        throw "Not monitor owner" ;
    }
    event.signal() ;

    mutex.unlock() ;
}
