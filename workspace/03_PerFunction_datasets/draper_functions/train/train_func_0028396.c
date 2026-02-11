IsAcceptedKey(wxKeyEvent& event)
{
    wxCHECK_MSG(Ok(), false, wxT("wxSheetCellEditor not created"));
    return M_CELLEDITORDATA->IsAcceptedKey(event);
}
