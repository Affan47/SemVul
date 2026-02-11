ParseSVNstate(const wxString &path, VCSstatearray &sa)
{
    if(!wxFileName::DirExists(wxFileName(path,_T(".svn")).GetFullPath()))
        return false;
    wxArrayString output;
    int hresult=::wxExecute(_T("svn stat -N ")+path,output,wxEXEC_SYNC);
    if(hresult!=0)
        return false;
    for(size_t i=0;i<output.GetCount();i++)
    {
        if(output[i].Len()<=7)
            break;
        VCSstate s;
        wxChar a=output[i][0];
        switch(a)
        {
            case ' ':
                s.state=fvsVcUpToDate;
                break;
            case '?':
                s.state=fvsVcNonControlled;
                break;
            case 'A':
                s.state=fvsVcAdded;
                break;
            case 'M':
                s.state=fvsVcModified;
                break;
            case 'C':
                s.state=fvsVcConflict;
                break;
            case 'D':
                s.state=fvsVcMissing;
                break;
            case 'I':
                s.state=fvsVcNonControlled;
                break;
            case 'X':
                s.state=fvsVcExternal;
                break;
            case '!':
                s.state=fvsVcMissing;
                break;
            case '~':
                s.state=fvsVcLockStolen;
                break;
            default:
                break;
        }
#ifdef __WXMSW__
        wxFileName f(output[i].Mid(7));
        f.MakeAbsolute(path);
        s.path=f.GetFullPath();
#else
        s.path=wxFileName(output[i].Mid(7)).GetFullPath();
#endif
        sa.Add(s);
    }
    return true;
}
