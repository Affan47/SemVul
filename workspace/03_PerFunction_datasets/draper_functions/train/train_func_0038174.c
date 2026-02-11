lock()
{
#ifndef NO_THREAD_CHECKS
    pthread_t tid = pthread_self();
    if (m_locked && m_lockedBy == tid) {
        cerr << "ERROR: Deadlock on mutex " << &m_mutex << endl;
    }
#endif
#ifdef DEBUG_MUTEX
    cerr << "MUTEX DEBUG: " << (void *)tid << ": Want to lock mutex " << &m_mutex << endl;
#endif
    pthread_mutex_lock(&m_mutex);
#ifndef NO_THREAD_CHECKS
    m_lockedBy = tid;
    m_locked = true;
#endif
#ifdef DEBUG_MUTEX
    cerr << "MUTEX DEBUG: " << (void *)tid << ": Locked mutex " << &m_mutex << endl;
#endif
}
