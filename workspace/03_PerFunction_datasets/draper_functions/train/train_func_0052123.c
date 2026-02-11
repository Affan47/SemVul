OnResize(wxSizeEvent& event)
{
    wxAuiTabCtrl* tabCtrl = (wxAuiTabCtrl*)event.GetEventObject();
    if (tabCtrl)
    {
        cbAuiNotebook* nb = (cbAuiNotebook*)tabCtrl->GetParent();
        if (nb)
        {
            if(nb->m_TabCtrlSize != event.GetSize())
            {
                nb->m_TabCtrlSize = event.GetSize();
                nb->MinimizeFreeSpace();
            }
        }
    }
    event.Skip();
}
