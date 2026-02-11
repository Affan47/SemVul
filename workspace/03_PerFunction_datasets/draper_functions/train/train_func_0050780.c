set_modes(const DataType &term, uint32 modes) {
    MutexLock thread_safe_method (m_impl->m_mutex);
    uint32 addr = m_impl->term_addr(term);
    m_impl->m_term_modes[addr] = modes;
}
