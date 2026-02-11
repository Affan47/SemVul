setName(const QString &name)
{
    d->m_Name = name;
    if (d->m_Name.startsWith(PAPERS_MARK)) {
        d->m_Type = ExtraDocument;
    }
    d->setDirty();
}
