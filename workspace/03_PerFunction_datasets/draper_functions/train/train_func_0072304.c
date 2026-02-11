workerThread(void * pthis) {
    Log::dbg("Thread started");
    GpsDevice * obj = (GpsDevice*)pthis;

    obj->doWork();

    Log::dbg("Thread finished");
    obj->threadId = 0;
    return NULL;
}
