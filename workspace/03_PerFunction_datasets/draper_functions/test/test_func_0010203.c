RebuildOpenFilesTree()
{
    if(Manager::IsAppShuttingDown())
        return;

    EditorManager* mgr = Manager::Get()->GetEditorManager();

    m_pTree->Freeze();
    m_pTree->DeleteChildren(m_pTree->GetRootItem());
    if(!mgr->GetEditorsCount())
    {
        m_pTree->Thaw();
        return;
    }

    for (int i = 0; i < mgr->GetEditorsCount(); ++i)
    {
        EditorBase* ed = mgr->GetEditor(i);
        if(!ed || !ed->VisibleToTree())
            continue;

        wxString shortname = ed->GetShortName();
        int mod = GetOpenFilesListIcon(ed);
        wxTreeItemId item = m_pTree->AppendItem(m_pTree->GetRootItem(), shortname, mod, mod, new OpenFilesListData(ed));
        if(mgr->GetActiveEditor() == ed)
            m_pTree->SelectItem(item);
    }

    m_pTree->SortChildren(m_pTree->GetRootItem());
    m_pTree->Expand(m_pTree->GetRootItem());
    m_pTree->Thaw();
}
