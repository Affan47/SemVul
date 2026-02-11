GetLanguageName(HighlightLanguage lang)
{
    if (lang == HL_NONE)
        return _("Plain text");
    wxString name = m_Sets[lang].m_Langs;
    if (!name.IsEmpty())
        return name;
    return _("Plain text");
}
