UpdateRows( size_t row, int numRows )
{
    wxSHEET_CHECKUPDATE_MSG(row, numRows, m_numRows, false)
    m_numRows += numRows;
    return HasOption(wxSHEET_ValueProviderColPref) ? DoUpdateRows(row, numRows) :
                                                     DoUpdateCols(row, numRows);
}
