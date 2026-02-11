GetCBConfigFile()

{
    PersonalityManager* PersMan = Manager::Get()->GetPersonalityManager();
    wxString personality = PersMan->GetPersonality();
    ConfigManager* CfgMan = Manager::Get()->GetConfigManager(_T("app"));
    wxString current_conf_file = CfgMan->LocateDataFile(personality+_T(".conf"), sdAllKnown);


    if (current_conf_file.IsEmpty())
    {
        wxString appdata;
        if ( personality == _T("default") )
            personality = _T("");

        wxGetEnv(_T("APPDATA"), &appdata);
        current_conf_file = appdata +

                    wxFILE_SEP_PATH + wxTheApp->GetAppName() + wxFILE_SEP_PATH
                    + personality + _T(".codesnippets.ini");
    }
    return current_conf_file;
}
