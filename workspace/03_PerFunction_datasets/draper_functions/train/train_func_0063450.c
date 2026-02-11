OnEnableSOCKSProxyCtrlUpdate(wxUpdateUIEvent& event) {
    if (m_EnableSOCKSProxyCtrl->IsEnabled() && m_EnableSOCKSProxyCtrl->IsChecked()) {
        m_SOCKSAddressCtrl->Enable(true);
        m_SOCKSPortCtrl->Enable(true);
        m_SOCKSUsernameCtrl->Enable(true);
        m_SOCKSPasswordCtrl->Enable(true);
		m_SOCKSNoProxiesCtrl->Enable(true);
    } else {
        m_SOCKSAddressCtrl->Enable(false);
        m_SOCKSPortCtrl->Enable(false);
        m_SOCKSUsernameCtrl->Enable(false);
        m_SOCKSPasswordCtrl->Enable(false);
		m_SOCKSNoProxiesCtrl->Enable(false);
    }
    event.Skip();
}
