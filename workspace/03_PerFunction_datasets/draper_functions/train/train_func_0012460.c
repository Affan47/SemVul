GetFirstNonEmptyColToLeft( const wxSheetCoords& coords ) const
{
    wxCHECK_MSG(ContainsCell(coords), coords.m_col - 1, wxT("Invalid coords"));
    if (HasOption(wxSHEET_ValueProviderColPref))
    {
        if (int(m_data.GetCount()) <= coords.m_row)
            return -1;
        if (int(m_data[coords.m_row].GetCount()) < coords.m_col)
            return m_data[coords.m_row].GetCount() - 1;
    }

    return coords.m_col - 1;
}
