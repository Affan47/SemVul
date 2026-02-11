OnProjectClose(CodeBlocksEvent& )

{


    if (Manager::IsAppShuttingDown())
        return;

    ProjectsArray* prjary = Manager::Get()->GetProjectManager()->GetProjects();
    if ( prjary->GetCount() )
        return;


    sDragScrollEvent dsEvt(wxEVT_S_DRAGSCROLL_EVENT, idDragScrollRescan);
    dsEvt.SetEventObject( m_pCB_AppWindow);
    dsEvt.SetString( _T("") );
    this->AddPendingEvent(dsEvt);
    return;
}
