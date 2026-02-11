CreateMenuViewLanguage(wxMenu* menuHilight)

{


    wxMenu* hl = menuHilight;


    int id = idEditHighlightModeText;
    hl->AppendRadioItem(id, _T("Plain text"),wxString::Format(_("Switch highlighting mode for current document to \"%s\""), _T("Plain text")));
    Connect(id, -1, wxEVT_COMMAND_MENU_SELECTED,
                    (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
                    &EditSnippetFrame::OnEditHighlightMode);


    {

        if (hl)
        {
            SEditorColourSet* theme = GetEditorManager()->GetColourSet();
            if (theme)
            {
                wxArrayString langs = theme->GetAllHighlightLanguages();
                for (size_t i = 0; i < langs.GetCount(); ++i)
                {
                    if (i > 0 && !(i % 20))
                        hl->Break();
                    int id = wxNewId();
                    hl->AppendRadioItem(id, langs[i],
                                wxString::Format(_("Switch highlighting mode for current document to \"%s\""), langs[i].c_str()));
                    Connect(id, -1, wxEVT_COMMAND_MENU_SELECTED,
                            (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
                            &EditSnippetFrame::OnEditHighlightMode);
                }
            }
        }
    }

}
