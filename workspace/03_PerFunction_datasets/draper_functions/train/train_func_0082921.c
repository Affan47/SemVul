ApplyColours()
{
    EditorColourSet* theme = Manager::Get()->GetEditorManager()->GetColourSet();
    if (theme)
    {
        wxString FontString = Manager::Get()->GetConfigManager(_T("editor"))->Read(_T("/font"), wxEmptyString);
        wxFont tmpFont(10, wxMODERN, wxNORMAL, wxNORMAL);

        if (!FontString.IsEmpty())
        {
            wxNativeFontInfo nfi;
            nfi.FromString(FontString);
            tmpFont.SetNativeFontInfo(nfi);
        }
        if (m_AutoCompTextControl)
        {
            m_AutoCompTextControl->StyleSetFont(wxSCI_STYLE_DEFAULT, tmpFont);
            theme->Apply(theme->GetHighlightLanguage(_T("C/C++")), m_AutoCompTextControl);
        }
    }
}
