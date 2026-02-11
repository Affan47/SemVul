GetCellBestSize(const wxSheetCoords& coords, wxDC *dc) const
{
    wxCHECK_MSG(ContainsCell(coords), wxSize(GetDefaultColWidth(), GetDefaultRowHeight()), wxT("Invalid coords"));
    wxSheetCellAttr attr(GetAttr(coords));
    wxSheet *sheet = (wxSheet*)this;
    wxSheetCellRenderer renderer(attr.GetRenderer(sheet, coords));
    if (!dc)
    {
        wxClientDC cdc(sheet);
        return renderer.GetBestSize(*sheet, attr, cdc, coords);
    }

    return renderer.GetBestSize(*sheet, attr, *dc, coords);
}
