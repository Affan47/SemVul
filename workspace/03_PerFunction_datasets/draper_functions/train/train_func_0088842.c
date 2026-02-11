GetVariableName(size_t n) const
{
    int numVars = GetNumberVariables();
    if (int(n) >= numVars) return wxEmptyString;
    wxString vars(GetVariableString());
    size_t i, count = 0, len = vars.Length();
    for (i = 0; i < len; i++)
    {
        if (n == count)
            return vars.Mid(i).BeforeFirst(wxT(','));
        if (vars[i] == wxT(','))
            count++;
    }

    return wxEmptyString;
}
