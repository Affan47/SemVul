OnEditorOpened(CodeBlocksEvent& event)
{
    EditorBase* eb = event.GetEditor();
    if (Manager::Get()->GetProjectManager()->IsBusy() && eb && (m_EditorArray.Index(eb) == wxNOT_FOUND))
    {
        m_EditorArray.Add(eb);
    }
    else
    {
        RefreshOpenFilesTree(eb);
    }
}
