OnUpdateUI(wxUpdateUIEvent& WXUNUSED(event))
{
    if(Manager::Get()->GetProjectManager()->GetProjects()->GetCount() == 0){
        m_pToolbar->Enable(false);
        wxMenuBar *menuBar =  Manager::Get()->GetAppFrame()->GetMenuBar();
        menuBar->FindItem(ID_MENU_DOXYWIZARD)->Enable(false);
        menuBar->FindItem(ID_MENU_EXTRACTPROJECT)->Enable(false);
        menuBar->FindItem(ID_MENU_BLOCKCOMMENT)->Enable(false);
        menuBar->FindItem(ID_MENU_LINECOMMENT)->Enable(false);
        menuBar->FindItem(ID_MENU_RUNHTML)->Enable(false);
        menuBar->FindItem(ID_MENU_RUNCHM)->Enable(false);
        menuBar->FindItem(ID_MENU_CONFIG)->Enable(false);
        menuBar->FindItem(ID_MENU_LOAD_TEMPLATE)->Enable(false);
        menuBar->FindItem(ID_MENU_SAVE_TEMPLATE)->Enable(false);
    }
}
