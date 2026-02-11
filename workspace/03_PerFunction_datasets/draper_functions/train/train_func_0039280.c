pauseIconUpdates()
{
    m_iconUpdatesPaused = true;
    foreach (KJob* job, m_previewJobs) {
        Q_ASSERT(job != 0);
        job->suspend();
    }
    m_scrollAreaTimer->start();
}
