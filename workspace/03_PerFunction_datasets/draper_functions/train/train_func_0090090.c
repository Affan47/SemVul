SettingsSaveWinPosition()

{


    wxFileConfig cfgFile(wxEmptyString,
                        wxEmptyString,
                        SettingsSnippetsCfgPath,
                        wxEmptyString,
                        wxCONFIG_USE_LOCAL_FILE);


    wxWindow* pwin = (wxWindow*)GetSnippetsWindow();
    if (pwin && IsPlugin() && pwin->GetParent() )
        pwin = pwin->GetParent();
    else return;
    int winXposn, winYposn, winWidth, winHeight;
    pwin->GetPosition( &winXposn, &winYposn );
    pwin->GetSize( &winWidth, &winHeight );

    wxString winPos;
    winPos = wxString::Format(wxT("%d %d %d %d"), winXposn,winYposn,winWidth,winHeight);
    cfgFile.Write(wxT("WindowPosition"),  winPos) ;
     LOGIT( _T("SavingWindowPosition[%s]"), winPos.c_str() );
    cfgFile.Flush();

}
