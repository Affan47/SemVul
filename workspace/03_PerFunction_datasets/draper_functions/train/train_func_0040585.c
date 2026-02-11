GetAttr(const wxSheetCoords& coords,
                                                 wxSheetAttr_Type type )
{
    switch (wxSheet::GetCellCoordsType(coords))
    {
        case wxSHEET_CELL_GRID :
        {
            switch (type)
            {
                case wxSHEET_AttrAny:
                {
                    wxSheetCellAttr attrCell(m_cellAttrs.GetValue(coords));
                    wxSheetCellAttr attrRow(m_rowAttrs.GetValue(coords.GetRow()));
                    wxSheetCellAttr attrCol(m_colAttrs.GetValue(coords.GetCol()));


                    wxPairArrayIntSheetCellAttr data;
                    if (attrCol.Ok())  data.SetValue(attrCol.GetLevel()+2, attrCol);
                    if (attrRow.Ok())  data.SetValue(attrRow.GetLevel()+1, attrRow);
                    if (attrCell.Ok()) data.SetValue(attrCell.GetLevel()+0, attrCell);


                    const int count = data.GetCount();

                    switch (count)
                    {
                        case 0  : return wxNullSheetCellAttr;
                        case 1  : return data.GetItemValue(0);
                        default : break;
                    }


                    wxSheetCellAttr attr;
                    attr.Copy(data.GetItemValue(0));
                    attr.SetDefaultAttr(data.GetItemValue(1));
                    if (count > 2)
                        data.GetItemValue(1).SetDefaultAttr(data.GetItemValue(2));


                    attr.SetKind(wxSHEET_AttrAny);

                    return attr;
                }
                case wxSHEET_AttrCell : return m_cellAttrs.GetValue(coords);
                case wxSHEET_AttrRow  : return m_rowAttrs.GetValue(coords.GetRow());
                case wxSHEET_AttrCol  : return m_colAttrs.GetValue(coords.GetCol());
                default:


                    break;
            }
            break;
        }
        case wxSHEET_CELL_ROWLABEL : return m_rowLabelAttrs.GetValue(coords.m_row);
        case wxSHEET_CELL_COLLABEL : return m_colLabelAttrs.GetValue(coords.m_col);
        default :
            wxFAIL_MSG(wxString::Format(wxT("Unhandled coords (%d, %d) in wxSheetCellAttrProvider::GetAttr"), coords.m_row, coords.m_col));
            break;
    }

    return wxNullSheetCellAttr;
}
