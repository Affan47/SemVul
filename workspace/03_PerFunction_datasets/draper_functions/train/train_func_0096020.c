OnEditorClosed(EditorBase* editor)
{

    wxString filename = editor->GetFilename();
    const int pos = m_StandaloneFiles.Index(filename);
    if (pos != wxNOT_FOUND)
    {
        m_StandaloneFiles.RemoveAt(pos);
        if (m_StandaloneFiles.IsEmpty())
            DeleteParser(NULL);
        else
            RemoveFileFromParser(NULL, filename);
    }
}
