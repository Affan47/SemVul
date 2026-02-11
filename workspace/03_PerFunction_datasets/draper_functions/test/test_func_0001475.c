GetMenu()
{
    wxMenuBar *menuBar = Manager::Get()->GetAppFrame()->GetMenuBar();
    cbAssert(menuBar);
    wxMenu *menu = NULL;

    int menu_pos = menuBar->FindMenu(_("&Debug"));

    if(menu_pos != wxNOT_FOUND)
        menu = menuBar->GetMenu(menu_pos);

    if (!menu)
    {
        menu = Manager::Get()->LoadMenu(_T("debugger_menu"),true);


        int finalPos = 5;
        int projcompMenuPos = menuBar->FindMenu(_("&Build"));
        if (projcompMenuPos == wxNOT_FOUND)
            projcompMenuPos = menuBar->FindMenu(_("&Compile"));

        if (projcompMenuPos != wxNOT_FOUND)
            finalPos = projcompMenuPos + 1;
        else
        {
            projcompMenuPos = menuBar->FindMenu(_("&Project"));
            if (projcompMenuPos != wxNOT_FOUND)
                finalPos = projcompMenuPos + 1;
        }
        menuBar->Insert(finalPos, menu, _("&Debug"));

        m_menuHandler->RebuildMenus();
    }
    return menu;
}
