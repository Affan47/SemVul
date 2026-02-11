GetThreadsCount() const
{
    if (!m_State.HasDriver())
        return 0;
    else
        return m_State.GetDriver()->GetThreads().size();
}
