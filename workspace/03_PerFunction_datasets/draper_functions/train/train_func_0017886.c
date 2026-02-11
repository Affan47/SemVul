GetVariableString() const
{
    wxCHECK_MSG(Ok(), wxEmptyString, wxT("invalid plotfunction"));
    return M_PLOTFUNCDATA->m_parser.GetVariableString();
}
