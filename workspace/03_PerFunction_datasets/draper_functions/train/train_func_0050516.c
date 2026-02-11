maybeSetDocumentDirty()
{
    if( m_doc )
        m_doc->forceDirty();

    incremenetVersion();
}
