BuildMenu(wxMenuBar* menuBar)
{
    if (!IsAttached() || !menuBar)
        return;

    m_Menu = Manager::Get()->LoadMenu(_T("project_import_menu"), false);
    if (!m_Menu)
        return;

    wxMenu* fileMenu = menuBar->GetMenu(0);
    if (fileMenu)
    {
        int menuId = 0, id = 0;
        wxMenuItemList menuItems = fileMenu->GetMenuItems();
        menuId = fileMenu->FindItem(_T("R&ecent files"));
        wxMenuItem* recentFileItem = fileMenu->FindItem(menuId);
        id = menuItems.IndexOf(recentFileItem);
        if (id == wxNOT_FOUND)
            id = 7;
        else
            ++id;


        fileMenu->Insert(++id, wxNewId(), _("&Import project"), m_Menu);
        fileMenu->InsertSeparator(++id);
    }
}
