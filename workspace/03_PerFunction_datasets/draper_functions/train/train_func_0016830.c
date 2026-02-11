Set( const wxPen &pen )
{
    wxCHECK_RET(Ok() && pen.Ok(), wxT("Invalid generic pen"));
    SetColour(pen.GetColour());
    M_GPENDATA->m_width = pen.GetWidth();
    M_GPENDATA->m_style = pen.GetStyle();
    M_GPENDATA->m_cap   = pen.GetCap();
    M_GPENDATA->m_join  = pen.GetJoin();

    wxDash* dash;
    int n_dashes = pen.GetDashes(&dash);
    SetDashes(n_dashes, dash);


}
