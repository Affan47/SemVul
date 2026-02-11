setEnabled(bool enabled)
{
    if (isEnabled() == enabled)
        return;
    m_enabled = enabled;
    emit rulesChanged();
}
