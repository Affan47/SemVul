setDocumentChanged(bool b)
{
    if (b && !m_docChanged)
        s_changedDocuments->append(this);
    else if (!b && m_docChanged)
        s_changedDocuments->removeAll(this);
    m_docChanged = b;
}
