SetProjectFile(ProjectFile* project_file, bool preserve_modified)
{
    if (m_pProjectFile == project_file)
        return;

    bool wasmodified = false;
    if(preserve_modified)
        wasmodified = GetModified();

    m_pProjectFile = project_file;
    if (m_pProjectFile)
    {

        m_Filename = UnixFilename(project_file->file.GetFullPath());

        m_pControl->GotoPos(m_pProjectFile->editorPos);
        m_pControl->ScrollToLine(m_pProjectFile->editorTopLine);
        m_pControl->ScrollToColumn(0);

        m_pProjectFile->editorOpen = true;

        if (Manager::Get()->GetConfigManager(_T("editor"))->ReadBool(_T("/tab_text_relative"), true))
            m_Shortname = m_pProjectFile->relativeToCommonTopLevelPath;
        else
            m_Shortname = m_pProjectFile->file.GetFullName();
        SetEditorTitle(m_Shortname);
    }

    if (!wxFileExists(m_Filename))
        m_pProjectFile->SetFileState(fvsMissing);
    else if (!wxFile::Access(m_Filename.c_str(), wxFile::write))
        m_pProjectFile->SetFileState(fvsReadOnly);

#if 0
    wxString dbg;
    dbg << _T("[ed] Filename: ") << GetFilename() << _T('\n');
    dbg << _T("[ed] Short name: ") << GetShortName() << _T('\n');
    dbg << _T("[ed] Modified: ") << GetModified() << _T('\n');
    dbg << _T("[ed] Project: ") << ((m_pProjectFile && m_pProjectFile->project) ? m_pProjectFile->project->GetTitle() : _T("unknown")) << _T('\n');
    dbg << _T("[ed] Project file: ") << (m_pProjectFile ? m_pProjectFile->relativeFilename : _T("unknown")) << _T('\n');
    Manager::Get()->GetLogManager()->DebugLog(dbg);
#endif
    if(preserve_modified)
        SetModified(wasmodified);
}
