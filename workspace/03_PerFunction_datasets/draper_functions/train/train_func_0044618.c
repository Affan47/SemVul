SetValue( const wxSheetCoords& coords_, const wxString& value )
{
    wxCHECK_RET(ContainsCell(coords_), wxT("Invalid coords"));
    wxSheetCoords coords(HasOption(wxSHEET_ValueProviderColPref) ? coords_ : coords_.GetSwapped());


    int count = m_data.GetCount();
    if (count <= coords.m_row)
    {
        wxArrayString sa;
        sa.Add( wxEmptyString, 1+coords.m_col );
        m_data.Insert( sa, count, 1+coords.m_row-count );
    }
    else
    {

        count = m_data[coords.m_row].GetCount();
        if (count <= coords.m_col)
        {
            m_data.Item(coords.m_row).Insert( wxEmptyString, count, 1+coords.m_col-count );
        }
    }
    m_data[coords.m_row][coords.m_col] = value;
}
