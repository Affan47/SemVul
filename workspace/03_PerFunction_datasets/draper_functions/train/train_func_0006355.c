get() throw(AssertException, exception)
    {
        if (!m_locked) {
            m_mutex.lock();
            m_locked = true;
        }
    }
