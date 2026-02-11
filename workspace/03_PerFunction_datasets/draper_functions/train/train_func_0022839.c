OnViewLayoutDelete(cb_unused wxCommandEvent& event)
{
    if (m_LastLayoutName == gDefaultLayout)
    {
        if (cbMessageBox(_("The default perspective cannot be deleted. It can always be reverted to "
                        "a predefined state though.\nDo you want to revert it now?"),
                        _("Confirmation"),
                        wxICON_QUESTION | wxYES_NO | wxNO_DEFAULT) == wxID_YES)
        {
            m_LayoutViews[gDefaultLayout] = gDefaultLayoutData;
            m_LayoutMessagePane[gDefaultLayout] = gDefaultMessagePaneLayoutData;
            LoadViewLayout(gDefaultLayout);
        }
        return;
    }

    if (m_LastLayoutName == gMinimalLayout)
    {
        if (cbMessageBox(_("The minimal layout cannot be deleted. It can always be reverted to "
                        "a predefined state though.\nDo you want to revert it now?"),
                        _("Confirmation"),
                        wxICON_QUESTION | wxYES_NO | wxNO_DEFAULT) == wxID_YES)
        {
            wxString tempLayout = m_PreviousLayoutName;
            m_LayoutViews[gMinimalLayout] = gMinimalLayoutData;
            m_LayoutMessagePane[gMinimalLayout] = gMinimalMessagePaneLayoutData;
            LoadViewLayout(gMinimalLayout);
            m_PreviousLayoutName = tempLayout;
        }
        return;
    }

    if (cbMessageBox(wxString::Format(_("Are you really sure you want to delete the perspective '%s'?"), m_LastLayoutName.wx_str()),
                    _("Confirmation"),
                    wxICON_QUESTION | wxYES_NO | wxNO_DEFAULT) == wxID_YES)
    {

        LayoutViewsMap::iterator it = m_LayoutViews.find(m_LastLayoutName);
        if (it != m_LayoutViews.end())
            m_LayoutViews.erase(it);
        it = m_LayoutMessagePane.find(m_LastLayoutName);
        if (it != m_LayoutMessagePane.end())
            m_LayoutMessagePane.erase(it);


        wxMenu* viewLayouts = nullptr;
        GetMenuBar()->FindItem(idViewLayoutSave, &viewLayouts);
        if (viewLayouts)
        {
            int id = viewLayouts->FindItem(m_LastLayoutName);
            if (id != wxNOT_FOUND)
                viewLayouts->Delete(id);

            PluginIDsMap::iterator it2 = m_PluginIDsMap.find(id);
            if (it2 != m_PluginIDsMap.end())
                m_PluginIDsMap.erase(it2);
        }

        cbMessageBox(wxString::Format(_("Perspective '%s' deleted.\nWill now revert to perspective '%s'..."), m_LastLayoutName.wx_str(), gDefaultLayout.wx_str()),
                        _("Information"), wxICON_INFORMATION);


        m_LastLayoutName = gDefaultLayout;
        LoadViewLayout(gDefaultLayout);
    }
}
