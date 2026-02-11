ParseCVSstate(const wxString &path, VCSstatearray &sa)
{
    wxArrayString output;
    wxString wdir=wxGetCwd();
    wxSetWorkingDirectory(path);
    int hresult=::wxExecute(_T("cvs stat -q -l  ."),output,wxEXEC_SYNC);
    if(hresult!=0)
        return false;
    wxSetWorkingDirectory(wdir);


    for(size_t i=0;i<output.GetCount();i++)
    {
        int ind1=output[i].Find(_T("File: "));
        int ind2=output[i].Find(_T("Status: "));
        if(ind1<0||ind2<0)
            return false;
        wxString state=output[i].Mid(ind2+8).Strip();
        VCSstate s;
        while(1)
        {
            if(state==_T("Up-to-date"))
            {
                s.state=fvsVcUpToDate;
                break;
            }
            if(state==_T("Locally Modified"))
            {
                s.state=fvsVcModified;
                break;
            }
            if(state==_T("Locally Added"))
            {
                s.state=fvsVcAdded;
                break;
            }
            break;
        }
        wxFileName f(output[i].Mid(ind1+6,ind2+6-ind1).Strip());
        f.MakeAbsolute(path);
        s.path=f.GetFullPath();
        sa.Add(s);
    }
    if(output.GetCount()>0)
        return true;
    else
        return false;
}
