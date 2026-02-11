GetValueTooltipFont()
{
    wxFont system = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    system.SetPointSize(std::max(system.GetPointSize() - 3, 7));
    wxString defaultFont = system.GetNativeFontInfo()->ToString();

    ConfigManager *c = Manager::Get()->GetConfigManager(wxT("debugger_common"));
    wxString configFont = c->Read(wxT("/common/tooltip_font"));

    return configFont.empty() ? defaultFont : configFont;
}
