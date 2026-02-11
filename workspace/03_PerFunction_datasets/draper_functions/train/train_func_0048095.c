getKeywordsString(KeywordCase kwc)
{
    wxArrayString keywordsArray(getKeywords(kwc));
    wxString keywords;
    for (size_t i = 0; i < keywordsArray.size(); ++i)
    {
        if (i)
            keywords += wxT(" ");
        keywords += keywordsArray[i];
    }
    return keywords;
}
