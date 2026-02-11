GetOptionByIndex(HighlightLanguage lang, int index)
{
    if (lang == HL_NONE)
        return nullptr;
    return m_Sets[lang].m_Colours.Item(index);
}
