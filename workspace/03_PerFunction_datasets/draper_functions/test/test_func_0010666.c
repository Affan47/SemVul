GetOptionInt(const wxString& name) const
{
    wxCHECK_MSG(M_PLOTCURVEDATA, 0, wxT("invalid plotcurve"));
    return wxAtoi(GetOption(name));
}
