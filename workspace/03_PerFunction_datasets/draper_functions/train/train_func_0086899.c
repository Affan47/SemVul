FitToPage(const wxWizardPageEx *page)
{
    wxCHECK_RET(!m_started, wxT("wxWizard::FitToPage after RunWizard"));

    while ( page )
    {
        wxSize size = page->GetBestSize();

        m_sizePage.IncTo(size);

        page = page->GetNext();
    }
}
