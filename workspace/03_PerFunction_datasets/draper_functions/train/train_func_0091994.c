Lock()
    {
        pthread_t current_thread = pthread_self();

        if (!pthread_equal(current_thread, fOwner)) {
            int res = pthread_mutex_lock(&fMutex);
            if (res == 0) {
                fOwner = current_thread;
                return true;
            } else {
                jack_error("JackBasePosixMutex::Lock res = %d", res);
                return false;
            }
        } else {
            return false;
        }
    }
