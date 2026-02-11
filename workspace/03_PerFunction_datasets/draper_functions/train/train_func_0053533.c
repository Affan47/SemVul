AddSheet(wxSheet* sheet)
{
    wxCHECK_RET(sheet, wxT("Invalid sheet"));


    if (!HasSheet(sheet))
        m_sheets.Add(sheet);
}
