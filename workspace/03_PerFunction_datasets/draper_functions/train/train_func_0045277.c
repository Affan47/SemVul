setShowFullPath(bool show)
{
    if (d->m_showFullPath != show) {
        d->m_showFullPath = show;
        d->updateContent();
    }
}
