StartCompileFile(wxFileName file)
{
    if (m_pProject)
    {
        if (!m_pProject->SaveAllFiles())
            Manager::Get()->GetLogManager()->Log(_("Could not save all files..."));

        file.MakeRelativeTo(m_pProject->GetBasePath());
    }

    wxString fname = file.GetFullPath();
    if (!fname.IsEmpty())
        CompileFile( UnixFilename(fname) );
}
