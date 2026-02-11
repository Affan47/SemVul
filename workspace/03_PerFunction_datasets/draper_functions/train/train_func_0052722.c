OnFileImportProjectMSVS(cb_unused wxCommandEvent& event)
{
    OpenGeneric(ShowOpenFileDialog(_("Import MS Visual Studio 7.0+ project"), FileFilters::GetFilterString(_T('.') + FileFilters::MSVC7_EXT)), false);
}
