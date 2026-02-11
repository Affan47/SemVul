get_global_attributes() const
{
    BOOST_LOG_EXPR_IF_MT(implementation::scoped_read_lock lock(m_impl->m_mutex);)
    return m_impl->m_global_attributes;
}
