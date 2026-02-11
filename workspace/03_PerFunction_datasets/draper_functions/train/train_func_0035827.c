OnTabPosition(wxCommandEvent& event)
{
    long style = m_pNotebook->GetWindowStyleFlag();
    style &= ~wxAUI_NB_BOTTOM;

    if (event.GetId() == idNBTabBottom)
        style |= wxAUI_NB_BOTTOM;
    m_pNotebook->SetWindowStyleFlag(style);

    Manager::Get()->GetConfigManager(_T("app"))->Write(_T("/environment/editor_tabs_bottom"), (bool)(style & wxAUI_NB_BOTTOM));
}
