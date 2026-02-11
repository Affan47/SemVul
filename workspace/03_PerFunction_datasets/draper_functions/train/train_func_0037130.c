AddCommandsBeforeBuild(const wxString& command)
{
    wxString envopt = command;
    m_CmdsBefore.Add(envopt);
    SetModified(true);
}
