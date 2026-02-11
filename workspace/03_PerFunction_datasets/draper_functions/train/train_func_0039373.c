ConvertTypeToAnchor(wxString fullType)
{
    static Token ancestorChecker(_T(""), 0, 0, 0);
    const wxString& argType = ExtractTypeAndName(fullType);
    if (!ancestorChecker.IsValidAncestor(argType))
        return fullType;

    size_t found = fullType.find(argType);
    fullType.replace(found, argType.size(), CommandToAnchor(cmdSearch, argType, &argType) );
    return fullType;
}
