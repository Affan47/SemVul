RunCompiledHelp(wxString sDocPath, wxString sPrjName)
{

    wxString sPathCHM = sDocPath + sPrjName + wxT(".chm");
    if(wxFile::Exists(sPathCHM)){
        wxString cmdCHM;
        wxString sCHMViewer = Manager::Get()->GetMacrosManager()->ReplaceMacros(m_pConfig->GetPathCHMViewer());
        if(sCHMViewer.IsEmpty()){

            if((wxPlatformInfo::Get().GetOperatingSystemId() & wxOS_WINDOWS) > 0){


                cmdCHM = wxT("CMD /C ") + sPathCHM;
            }
            else{
                cmdCHM = sPathCHM;
            }
        }
        else{
            cmdCHM = sCHMViewer + wxT(" ") + sPathCHM;
        }
        wxProcess *proc = wxProcess::Open(cmdCHM);
        if(proc == NULL){
            AppendToLog(wxString::Format(_("Execution of '%s' failed."), cmdCHM.c_str()), LOG_ERROR);
        }
        else{
            AppendToLog(wxString::Format(_("Process %ld (%s) launched."), proc->GetPid(), cmdCHM.c_str()));
        }
    }
    else{
        AppendToLog(_("HTML Help not found at ") + sPathCHM + wxT("."), LOG_WARNING);
    }
}
