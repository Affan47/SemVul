GetOptionByName(HighlightLanguage lang, const wxString& name)
{
    if (lang == HL_NONE)
        return 0L;
    SOptionSet& mset = m_Sets[lang];
    for (unsigned int i = 0; i < mset.m_Colours.GetCount(); ++i)
    {
        SOptionColour* opt = mset.m_Colours.Item(i);
        if (opt->name == name)
            return opt;
    }
    return 0L;
}
