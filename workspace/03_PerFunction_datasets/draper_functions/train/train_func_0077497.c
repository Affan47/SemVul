OnViewCategorize(wxCommandEvent& event)
{
    bool do_categorise = event.IsChecked();

    if (do_categorise)
        m_TreeVisualState |=  ptvsCategorize;
    else
        m_TreeVisualState &= ~ptvsCategorize;

    Manager::Get()->GetAppFrame()->GetMenuBar()->Check(idMenuViewCategorize, do_categorise);
    Manager::Get()->GetConfigManager(_T("project_manager"))->Write(_T("/categorize_tree"), do_categorise);

    RebuildTree();
}
