Create( const wxPlotFunction& curve )
{
    wxCHECK_MSG(curve.Ok(), false, wxT("invalid plot function"));
    UnRef();
    Ref(curve);
    return true;
}
