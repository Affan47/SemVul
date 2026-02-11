SetDescription( const wxString& label, const wxString& content )
{
    if ( m_pTxtHelpCaption )
    {
        wxSize osz1 = m_pTxtHelpCaption->GetSize();
        wxSize osz2 = m_pTxtHelpContent->GetSize();

        m_pTxtHelpCaption->SetLabel(label);
        m_pTxtHelpContent->SetLabel(content);

        m_pTxtHelpCaption->SetSize(-1,osz1.y);
        m_pTxtHelpContent->SetSize(-1,osz2.y);

        UpdateDescriptionBox( m_splitterY, m_width, m_height );
    }
}
