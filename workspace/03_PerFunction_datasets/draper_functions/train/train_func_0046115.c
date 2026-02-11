killPreviewJobs()
{
    foreach (KJob* job, m_previewJobs) {
        Q_ASSERT(job != 0);
        job->kill();
    }
    m_previewJobs.clear();
    m_sequenceIndices.clear();

    m_iconUpdateTimer->stop();
    m_scrollAreaTimer->stop();
    m_changedItemsTimer->stop();
}
