OnEditorClose(CodeBlocksEvent& WXUNUSED(event))
{
    if(IsAttached()){
        if(Manager::Get()->GetEditorManager()->GetEditorsCount() == 0){
            m_pToolbar->EnableTool(ID_TB_BLOCKCOMMENT, false);
            m_pToolbar->EnableTool(ID_TB_LINECOMMENT, false);
            wxMenuBar *menuBar =  Manager::Get()->GetAppFrame()->GetMenuBar();
            menuBar->FindItem(ID_MENU_BLOCKCOMMENT)->Enable(false);
            menuBar->FindItem(ID_MENU_LINECOMMENT)->Enable(false);
        }
    }
}
