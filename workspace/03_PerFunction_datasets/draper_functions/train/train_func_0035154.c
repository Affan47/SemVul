OnPageChanging( wxWizardExEvent& event ) {
    CMainDocument* pDoc = wxGetApp().GetDocument();
    wxString       strBuffer = wxEmptyString;
    long           lBuffer = 0;

    wxASSERT(pDoc);
    wxASSERT(wxDynamicCast(pDoc, CMainDocument));

    if (event.GetDirection() == true) {

        pDoc->proxy_info.use_http_proxy = (m_pProxyHTTPServerCtrl->GetValue().Length() > 0);
        pDoc->proxy_info.http_server_name = (const char*)m_pProxyHTTPServerCtrl->GetValue().mb_str();
        pDoc->proxy_info.http_user_name = (const char*)m_pProxyHTTPUsernameCtrl->GetValue().mb_str();
        pDoc->proxy_info.http_user_passwd = (const char*)m_pProxyHTTPPasswordCtrl->GetValue().mb_str();

        strBuffer = m_pProxyHTTPPortCtrl->GetValue();
        strBuffer.ToLong((long*)&lBuffer);
        pDoc->proxy_info.http_server_port = lBuffer;

        pDoc->proxy_info.use_socks_proxy = (m_pProxySOCKSServerCtrl->GetValue().Length() > 0);
        pDoc->proxy_info.socks_server_name = (const char*)m_pProxySOCKSServerCtrl->GetValue().mb_str();
        pDoc->proxy_info.socks5_user_name = (const char*)m_pProxySOCKSUsernameCtrl->GetValue().mb_str();
        pDoc->proxy_info.socks5_user_passwd = (const char*)m_pProxySOCKSPasswordCtrl->GetValue().mb_str();

        strBuffer = m_pProxySOCKSPortCtrl->GetValue();
        strBuffer.ToLong((long*)&lBuffer);
        pDoc->proxy_info.socks_server_port = lBuffer;

        pDoc->SetProxyConfiguration();
    }
}
