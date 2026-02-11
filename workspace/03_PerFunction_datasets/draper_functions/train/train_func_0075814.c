SetOutputFilename(const wxString& filename)
{
    if (filename.IsEmpty())
    {
        m_OutputFilename = SuggestOutputFilename();
        SetModified(true);
        return;
    }
    else if (m_OutputFilename == filename)
        return;
    m_OutputFilename = UnixFilename(filename);
    GenerateTargetFilename(m_OutputFilename);
    SetModified(true);
}
