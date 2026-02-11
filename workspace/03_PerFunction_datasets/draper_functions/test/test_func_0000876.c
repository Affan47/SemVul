DrawSplitterButton(wxDC &dc, const wxRect& rect)
{


    wxPen highlight(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNHIGHLIGHT), 1, wxSOLID);
    wxPen shadow(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNSHADOW), 1, wxSOLID);
    wxPen darkShadow(wxSystemSettings::GetColour(wxSYS_COLOUR_3DDKSHADOW), 1, wxSOLID);

    dc.SetPen(shadow);
    dc.SetBrush(wxBrush(GetBackgroundColour(), wxSOLID));
    dc.DrawRectangle(rect);
    dc.DrawLine(rect.GetRight()-1, rect.y+2, rect.GetRight()-1, rect.GetBottom()-1);
    dc.DrawLine(rect.x+2, rect.GetBottom()-1, rect.GetRight(), rect.GetBottom()-1);

    dc.SetPen(darkShadow);
    dc.DrawLine(rect.GetRight(), rect.y+1, rect.GetRight(), rect.GetBottom());
    dc.DrawLine(rect.x+1, rect.GetBottom(), rect.GetRight(), rect.GetBottom());

    dc.SetPen(highlight);
    dc.DrawLine(rect.x+1, rect.y+1, rect.GetRight()-1, rect.y+1);
    dc.DrawLine(rect.x+1, rect.y+1, rect.x+1, rect.GetBottom()-1);
}
