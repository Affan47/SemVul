FindFunctionOpenParenthesis(const wxString& calltip)
{
    int nest = 0;
    for (size_t i = calltip.length(); i > 0; --i)
    {
        wxChar c = calltip[i - 1];
        if (c == wxT('('))
        {
            --nest;
            if (nest == 0)
            return i - 1;
        }
        else if (c == wxT(')'))
            ++nest;
    }
    return -1;
}
