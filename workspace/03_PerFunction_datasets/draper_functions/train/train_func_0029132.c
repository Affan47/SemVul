CreateTopRightSheet(wxWindowID id)
{
    wxSheet *sheet = CreateSheet(id);
    wxCHECK_MSG(sheet, NULL, wxT("Unable to create wxSheet child in splitter"));
    sheet->RefSheet(m_tlSheet);
    sheet->GetRowLabelWindow()->Show(false);
    sheet->GetCornerLabelWindow()->Show(false);
    sheet->EnableSplitHorizontally(false);
    sheet->SetGridOrigin(m_tlSheet->GetGridOrigin());
    return sheet;
}
