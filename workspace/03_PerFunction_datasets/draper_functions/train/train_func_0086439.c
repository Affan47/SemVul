OnColoursCopyAllFrom(cb_unused wxCommandEvent &event)
{
    const wxArrayString &listLang = m_Theme->GetAllHighlightLanguages();

    wxMenu menu;
    for (size_t ii = 0; ii < listLang.GetCount(); ++ii)
    {
        MenuItemLanguageOptionID id;
        id.index = -1;
        id.langID = m_Theme->GetHighlightLanguage(listLang[ii]);;

        long menuID = wxNewId();

        menu.Append(menuID, listLang[ii]);
        Connect(menuID, wxEVT_COMMAND_MENU_SELECTED,
                wxCommandEventHandler(EditorConfigurationDlg::OnMenuColoursCopyAllFrom));
        m_MenuIDToLanguageOption.insert(MenuIDToLanguageOption::value_type(menuID, id));
    }

    PopupMenu(&menu);

    for (MenuIDToLanguageOption::const_iterator it = m_MenuIDToLanguageOption.begin();
         it != m_MenuIDToLanguageOption.end();
         ++it)
    {
        Disconnect(it->first, wxEVT_COMMAND_MENU_SELECTED,
                   wxCommandEventHandler(EditorConfigurationDlg::OnMenuColoursCopyAllFrom));
    }
    m_MenuIDToLanguageOption.clear();
}
