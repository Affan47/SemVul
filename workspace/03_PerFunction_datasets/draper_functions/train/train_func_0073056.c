free(Job *job)
{
    Plasma::AbstractRunner *runner = static_cast<FindMatchesJob*>(job)->runner();
    QMutexLocker l(&m_mutex);

    --m_runCounts[runner->name()];
}
