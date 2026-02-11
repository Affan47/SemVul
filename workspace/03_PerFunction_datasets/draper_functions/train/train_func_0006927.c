SetCaseSensitivity(HighlightLanguage lang, bool CaseSensitive)
{
    if ( lang == HL_NONE )
        return;

    m_Sets[lang].m_CaseSensitive = CaseSensitive;
}
