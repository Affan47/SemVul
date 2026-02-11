Configure()
{
    CodeBlocksEvent event(cbEVT_MENUBAR_CREATE_BEGIN);
    Manager::Get()->ProcessEvent(event);

    ConfigureToolsDlg dlg(Manager::Get()->GetAppWindow());
    PlaceWindow(&dlg);
    dlg.ShowModal();
    SaveTools();
    BuildToolsMenu(m_Menu);

    CodeBlocksEvent event2(cbEVT_MENUBAR_CREATE_END);
    Manager::Get()->ProcessEvent(event2);

    return 0;
}
