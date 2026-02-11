GetProjectConfigurationPanel(wxWindow* parent, cbProject* project)
{
    return new CCOptionsProjectDlg(parent, project, &m_NativeParser);
}
