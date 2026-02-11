blockOnCheck(const boost::function<bool ()> &check)
{
    DynMutex::Guard guard = m_mutex.lock();


    if (check()) {
        m_checks.insert(&check);
        do {
             m_cond.wait(m_mutex);
        } while (m_checks.find(&check) != m_checks.end());
    }
}
