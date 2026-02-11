GetCleanSingleFileCommand(const wxString& filename) const
{
    wxArrayString ret;


    FileType ft = FileTypeOf(filename);


    if (ft != ftSource)
        return ret;

    wxFileName fname(filename);
    fname.SetExt(m_pCompiler->GetSwitches().objectExtension);
    wxString o_filename = fname.GetFullPath();
    fname.SetExt(FileFilters::EXECUTABLE_EXT);
    wxString exe_filename = fname.GetFullPath();

    ret.Add(o_filename);
    ret.Add(exe_filename);

    return ret;
}
