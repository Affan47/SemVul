StopImp(jack_native_thread_t thread)
{
    if (thread != (jack_native_thread_t)NULL) {
        jack_log("JackPosixThread::Stop");
        void* status;
        pthread_join(thread, &status);
        return 0;
    } else {
        return -1;
    }
}
