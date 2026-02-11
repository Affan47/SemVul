EndEdit(const wxSheetCoords& coords, wxSheet* sheet)
{
    wxCHECK_MSG(Ok(), false, wxT("wxSheetCellEditor not created"));
    return M_CELLEDITORDATA->EndEdit(coords, sheet);
}
