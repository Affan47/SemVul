getPreferredStepSize() const
{
    if (!m_handle) return 0;
    return m_descriptor->getPreferredStepSize(m_handle);
}
