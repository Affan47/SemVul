BuildToolBar(wxToolBar* toolBar)
{
    Manager::Get()->AddonToolBar(toolBar,_T("codecompletion_toolbar"));

    m_Function = XRCCTRL(*toolBar, "chcCodeCompletionFunction", wxChoice);
    m_Scope    = XRCCTRL(*toolBar, "chcCodeCompletionScope",    wxChoice);

    m_ToolBar = toolBar;
    UpdateToolBar();
    EnableToolbarTools(false);

    return true;
}
