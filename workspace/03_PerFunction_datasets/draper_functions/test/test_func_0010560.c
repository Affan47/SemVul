instance() {
        static UriRegistrar *inst = 0;
        static QMutex mutex;
        mutex.lock();
        if (inst == 0) inst = new UriRegistrar();
        mutex.unlock();
        return inst;
    }
