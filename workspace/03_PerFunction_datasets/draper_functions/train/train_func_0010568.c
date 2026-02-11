AddCompilerPage(const wxString& compilerID, const wxString& validCompilerIDs, bool allowCompilerChange, bool allowConfigChange)
{
    if (m_pWizCompilerPanel)
        return;
    m_pWizCompilerPanel = new WizCompilerPanel(compilerID, validCompilerIDs, m_pWizard, m_Wizards[m_LaunchIndex].wizardPNG, allowCompilerChange, allowConfigChange);
    if (!m_pWizCompilerPanel->SkipPage())
        m_Pages.Add(m_pWizCompilerPanel);
    else
    {
        delete m_pWizCompilerPanel;
        m_pWizCompilerPanel = 0;
    }
}
