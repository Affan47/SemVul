HasFont() const
{
    wxCHECK_MSG(m_refData, false, wxT("wxSheetCellAttr not initializied"));
    return M_CELLATTRDATA->m_font.Ok();
}
