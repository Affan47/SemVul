SetModified(bool modified)
{
    if (modified != m_Modified)
    {
        m_Modified = modified;
        if (!m_Modified)
        {
            m_pControl->SetSavePoint();
        }
        SetEditorTitle(m_Shortname);
        NotifyPlugins(cbEVT_EDITOR_MODIFIED);

        if (m_pProjectFile)
            m_pProjectFile->SetFileState(m_pControl->GetReadOnly() ? fvsReadOnly : (m_Modified ? fvsModified : fvsNormal));
    }
}
