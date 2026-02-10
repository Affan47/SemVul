OnViewMenuUpdateUI(wxUpdateUIEvent& event)
{
    if (Manager::IsAppShuttingDown())
    {
        event.Skip();
        return;
    }

    wxMenuBar* mbar   = GetMenuBar();
    cbEditor*  ed     = Manager::Get()->GetEditorManager() ? Manager::Get()->GetEditorManager()->GetBuiltinActiveEditor() : nullptr;
    bool       manVis = m_LayoutManager.GetPane(m_pPrjManUI->GetNotebook()).IsShown();

    mbar->Check(idViewManager,             manVis);
    mbar->Check(idViewLogManager,          m_LayoutManager.GetPane(m_pInfoPane).IsShown());
    mbar->Check(idViewStartPage,           Manager::Get()->GetEditorManager()->GetEditor(g_StartHereTitle)!=NULL);
    mbar->Check(idViewStatusbar,           GetStatusBar() && GetStatusBar()->IsShown());
    mbar->Check(idViewScriptConsole,       m_LayoutManager.GetPane(m_pScriptConsole).IsShown());
    mbar->Check(idViewHideEditorTabs,      Manager::Get()->GetEditorManager()->GetNotebook()->GetTabCtrlHeight() == 0);
    mbar->Check(idViewFullScreen,          IsFullScreen());
    mbar->Enable(idViewFocusEditor,        ed);
    mbar->Enable(idViewFocusManagement,    manVis);
    mbar->Enable(idViewFocusLogsAndOthers, m_pInfoPane->IsShown());


    mbar->Check(idViewToolMain,     m_LayoutManager.GetPane(m_pToolbar).IsShown());
    mbar->Check(idViewToolDebugger, m_LayoutManager.GetPane(m_debuggerToolbarHandler->GetToolbar(false)).IsShown());
    wxMenu* viewToolbars = nullptr;
    GetMenuBar()->FindItem(idViewToolMain, &viewToolbars);
    if (viewToolbars)
    {
        for (size_t i = 0; i < viewToolbars->GetMenuItemCount(); ++i)
        {
            wxMenuItem* item = viewToolbars->GetMenuItems()[i];
            wxString pluginName = m_PluginIDsMap[item->GetId()];
            if (!pluginName.IsEmpty())
            {
                cbPlugin* plugin = Manager::Get()->GetPluginManager()->FindPluginByName(pluginName);
                if (plugin)
                    item->Check(m_LayoutManager.GetPane(m_PluginsTools[plugin]).IsShown());
            }
        }
    }

    event.Skip();
}
