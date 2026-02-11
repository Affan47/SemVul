CreateIDE()
{
    int leftW = Manager::Get()->GetConfigManager(_T("app"))->ReadInt(_T("/main_frame/layout/left_block_width"), 200);
    wxSize clientsize = GetClientSize();


    m_pCloseFullScreenBtn = new wxButton(this, idCloseFullScreen, _( "Close full screen" ), wxDefaultPosition );
    m_pCloseFullScreenBtn->Show( false );


    m_pPrjMan = Manager::Get()->GetProjectManager();
    m_pPrjManUI = new ProjectManagerUI;
    m_pPrjMan->SetUI(m_pPrjManUI);
    m_LayoutManager.AddPane( m_pPrjManUI->GetNotebook(),
                             wxAuiPaneInfo().Name(wxT("ManagementPane")).Caption(_("Management")).
                                 BestSize(wxSize(leftW, clientsize.GetHeight())).
                                 MinSize(wxSize(100,100)).Left().Layer(1) );


    SetupGUILogging();
    SetupDebuggerUI();

    CreateMenubar();

    m_pEdMan  = Manager::Get()->GetEditorManager();
    m_pLogMan = Manager::Get()->GetLogManager();


    m_LayoutManager.AddPane(m_pEdMan->GetNotebook(), wxAuiPaneInfo().Name(wxT("MainPane")).
                            CentrePane());


    m_pScriptConsole = new ScriptConsole(this, -1);
    m_LayoutManager.AddPane(m_pScriptConsole, wxAuiPaneInfo().Name(wxT("ScriptConsole")).
                            Caption(_("Scripting console")).Float().MinSize(100,100).FloatingPosition(300, 200).Hide());

    DoUpdateLayout();
    DoUpdateLayoutColours();
    DoUpdateEditorStyle();

    m_pEdMan->GetNotebook()->SetDropTarget(new cbFileDropTarget(this));
    m_pPrjManUI->GetNotebook()->SetDropTarget(new cbFileDropTarget(this));

    Manager::Get()->GetColourManager()->Load();
}
