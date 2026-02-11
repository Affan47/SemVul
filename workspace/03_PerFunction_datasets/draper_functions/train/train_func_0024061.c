startPreviewJob(const KFileItemList& items, int width, int height)
{
    if (items.count() > 0) {
        KIO::PreviewJob* job = KIO::filePreview(items, QSize(width, height), &m_enabledPlugins);


        if (!m_sequenceIndices.isEmpty() && (items.count() == 1)) {
            QMap<KUrl, int>::iterator it = m_sequenceIndices.find(items[0].url());
            if (it != m_sequenceIndices.end()) {
                job->setSequenceIndex(*it);
            }
        }

        connect(job, SIGNAL(gotPreview(KFileItem,QPixmap)),
                q, SLOT(addToPreviewQueue(KFileItem,QPixmap)));
        connect(job, SIGNAL(finished(KJob*)),
                q, SLOT(slotPreviewJobFinished(KJob*)));
        m_previewJobs.append(job);
    }
}
