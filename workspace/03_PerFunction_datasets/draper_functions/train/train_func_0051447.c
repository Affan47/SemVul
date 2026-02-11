FindAppPath(const wxString& argv0, const wxString& cwd, const wxString& appVariableName)

{


    wxString str;


    if (!appVariableName.IsEmpty())
    {
        str = wxGetenv(appVariableName);
        if (!str.IsEmpty())
            return str;
    }

#if defined(__WXMAC__) && !defined(__DARWIN__)


    return cwd;
#endif

    wxString argv0Str = argv0;
    #if defined(__WXMSW__)
        do{
            if (argv0Str.Contains(wxT(".exe")) ) break;
            if (argv0Str.Contains(wxT(".bat")) ) break;
            if (argv0Str.Contains(wxT(".cmd")) ) break;
            argv0Str.Append(wxT(".exe"));
        }while(0);
    #endif

    if (wxIsAbsolutePath(argv0Str))
    {
        #if defined(LOGGING)
        LOGIT( _T("FindAppPath: AbsolutePath[%s]"), wxPathOnly(argv0Str).GetData() );
        #endif
        return wxPathOnly(argv0Str);
    }
    else
    {

        wxString currentDir(cwd);
        if (currentDir.Last() != wxFILE_SEP_PATH)
            currentDir += wxFILE_SEP_PATH;

        str = currentDir + argv0Str;
        if (wxFileExists(str))
        {
            #if defined(LOGGING)
            LOGIT( _T("FindAppPath: RelativePath[%s]"), wxPathOnly(str).GetData() );
            #endif
            return wxPathOnly(str);
        }
    }


    wxPathList pathList;
    pathList.AddEnvList(wxT("PATH"));
    str = pathList.FindAbsoluteValidPath(argv0Str);
    if (!str.IsEmpty())
    {
        #if defined(LOGGING)
        LOGIT( _T("FindAppPath: SearchPath[%s]"), wxPathOnly(str).GetData() );
        #endif
        return wxPathOnly(str);
    }


     #if defined(LOGGING)
     LOGIT(  _T("FindAppPath: Failed, returning cwd") );
     #endif
    return wxEmptyString;

}
