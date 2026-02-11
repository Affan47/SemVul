close() {
    MutexLock thread_safe_method(m_impl->m_mutex);
    _close();
}
