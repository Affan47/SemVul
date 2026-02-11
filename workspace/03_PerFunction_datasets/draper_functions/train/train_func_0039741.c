PaintBackground(wxSheet& , const wxSheetCellAttr& attr,
                                               wxDC& dc, const wxRect& rect,
                                               const wxSheetCoords& , bool )
{

    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.SetBrush(wxBrush(attr.GetBackgroundColour(), wxSOLID));


    dc.DrawRectangle(rect);

    if (GetControl())
        GetControl()->Refresh();
}
